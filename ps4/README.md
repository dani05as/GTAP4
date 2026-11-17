# ParadiseGTA — port a PS4 / GoldHEN (GTA V 1.57)

Port del menú **ParadiseGTA** (SPRX de PS3, 62 000 líneas, liberado por gopro_2027)
a la **nueva generación: PS4 con GoldHEN, GTA V 1.57**.

Esta carpeta es el proyecto PS4. La base de PS3 original quedó **intacta** en
`../ParadiseGTA_optimized_2020/`, porque se usa
como fuente de verdad para regenerar la capa de natives y para copiar páginas.

---

## 1. Qué se hizo (y qué no se puede hacer)

Antes que nada, la verdad técnica: **no existe forma de "trasvasar tal cual" un
SPRX de PS3 a PS4.** No es cuestión de voluntad, es la arquitectura:

| PS3 (SPRX) | PS4 (GoldHEN) |
|---|---|
| PowerPC Cell (PPU), big-endian | x86-64, little-endian |
| punteros de 32 bits | punteros de 48 bits |
| natives con hash de 32 bits (`0x6E31E993`) | hash de 64 bits (`0x43A66C31C68491C0`) |
| argumentos de native de 4 bytes | argumentos de 8 bytes |
| `sys_ppu_thread_create`, `cellFs`, `cellPad`, `sysutil` | `sceKernel*`, stdio musl, natives de input |
| tablas de direcciones de 32 bits descargadas de un servidor (`addrstruct()`) | no existen en PS4: hay que descubrirlas |
| OPD, TOC, ensamblador PPU (`lis %r3, 0xFFEE`) | no aplica |
| RPC/RTM sobre PSN + cifrado propio | el servicio está muerto; el cifrado no hace falta |

Concreto, del código original:

```cpp
static NativeArg_s* NativeArg = (NativeArg_s*)0x10060000;   // memoria fija de PS3
unsigned int TunablePointer = 0x1E70374;                     // offset del ebuild de PS3
struct Native_s { unsigned int NativeFunctions[7]; ... };    // punteros de 32 bits
__asm("lis %r3, 0xFFEE");                                     // PowerPC
```

Nada de eso tiene sentido en PS4. **Lo que sí se reutiliza es lo que importa:**

- ✅ **el 98,5 % de la capa de natives** (4.577 de 4.646) se traduce automáticamente
- ✅ **el framework del menú** (dibujo, input, opciones, submenús, scroll, colores)
- ✅ **las páginas/features que sólo llaman natives** (la mayoría del menú)
- ⚠️ **lo que toca memoria directamente** (protección anti-modder, freeze, force host,
  recovery, RCE/RTM) necesita offsets de 1.57 que **no están en el repo** y hay que
  sacarlos con ingeniería inversa propia. Ver §6.

---

## 2. Estado del port

| pieza | estado |
|---|---|
| Capa de natives PS3 → 1.57 (nombres + hashes 64-bit) | ✅ automática, 98,5 % |
| Invoker x86-64 (contexto, args de 8 bytes, floats, Vector3) | ✅ escrito + calibración en runtime |
| Descubrimiento de la tabla de natives de 1.57 | ✅ por validación (sin firma fija) |
| Framework de menú (mismo layout, mismas funciones `addOption…`) | ✅ portado |
| Páginas de referencia (10) | ✅ portadas y probadas en host |
| Entrada GoldHEN (`plugin_load`, metadatos, hilo) | ✅ |
| Build system (OpenOrbis + GoldHEN SDK vendorizado) | ✅ (requiere toolchain) |
| Self-test sin consola (mismo código, natives falsos) | ✅ 0 fallos, 31 929 llamadas |
| Validación **en consola** | ⚠️ falta: no hay PS4 en este entorno |
| Offsets 1.57 para features de memoria | ⚠️ los tiene que aportar quien lo pruebe |
| RCE / RTM / money recovery | ❌ no es portable (servicios PSN dados de baja) |

> Importante: **el código compila y el menú se ejecuta de punta a punta en el
> self-test** (`make hostcheck`), pero nadie lo corrió todavía en una PS4 real.
> Las tres piezas que necesitan consola para confirmarse están marcadas con
> `TODO(consola)` en el código: descubrimiento de la tabla, calibración del
> contexto y el dibujado desde el hilo del plugin.

---

## 3. Cómo se traduce la capa de natives (la parte que hice automática)

El hash de PS3 es `joaat32(nombre_en_minúsculas)`. El de PS4/1.57 **no se deriva**
de ése, así que el único puente es la **identidad** del native. Hay dos claves de
identidad que sobreviven a 10 años de parches:

1. **el nombre** → resuelve el renombre masivo de 2017 (`_SET_TEXT_ENTRY` →
   `BEGIN_TEXT_COMMAND_DISPLAY_TEXT`, etc.)
2. **el `jhash` de 32 bits** → Rockstar **nunca cambia el hash al renombrar**, y la
   base moderna trae el `jhash` de cada native. Esto resuelve incluso los ~2 000
   natives que el header de 2015 sólo conoce como `_0xDEADBEEF`.

Resultado (`build/native_report.md`, regenerable con `make natives`):

```
natives en el Natives.h de PS3 ........ 4 646
mapeados a hash de 64 bits ............ 4 577  (98,5 %)
renombrados por Rockstar remapeados ... 2 069
ya no existen en 1.57 (stub seguro) ...    69
diferencia de argumentos ..............   189
punteros 32→64 corregidos por deref ...    33
```

- Los **69** que faltan son casi todos de PSN/party (`NETWORK_SESSION_ENTER`,
  `NETWORK_IS_IN_PARTY`, `SET_PAD_SHAKE`…). Se generan como *stub*: compilan,
  escriben una línea en klog y devuelven 0 en vez de romper el juego.
- Los **33 deref** son casos donde PS3 pasaba un handle por puntero y PS4 lo recibe
  por valor (`DELETE_ENTITY(Entity*)`). Se genera `*param` automáticamente.
- Los **189** de diferencia de argumentos quedan listados en el reporte: son
  natives a los que Rockstar les agregó/sacó parámetros. El generador rellena con 0
  los nuevos del final (para que el slot no tenga basura) y descarta los que sobran.

Todo esto vive en `include/natives_ps4.h` (**generado, no editar a mano**) y es un
*reemplazo directo* del `Natives.h` de PS3: **mismos namespaces, mismos nombres,
mismos argumentos**. Por eso `Mods.h` compila sin tocar una sola llamada:

```cpp
// igual que en PS3, pero ahora llama al native de 1.57
PLAYER::GET_PLAYER_PED(player)   // -> invoke_native<Ped>(0x43A66C31C68491C0ULL, player)
```

---

## 4. Compilar

### Requisitos

- **OpenOrbis PS4 Toolchain** v0.5.4 (clang/LLVM 18, musl, `create-fself`)
- `python3` (para regenerar la capa de natives)
- `g++` (sólo si querés correr el self-test en la PC)

```bash
export OO_PS4_TOOLCHAIN=/ruta/a/OpenOrbis-PS4-Toolchain
cd ps4
./build.sh            # regenera natives + verifica hashes + self-test + .prx
```

o por partes:

```bash
make natives     # include/natives_ps4.h + build/native_report.md
make             # build/paradise_gta.prx
make hostcheck   # corre el menú en la PC con natives falsos
```

Salida: **`build/paradise_gta.prx`**.

### Instalar en la consola

1. Copiar `paradise_gta.prx` a `/data/GoldHEN/plugins/`
2. (Opcional) copiar `offsets.example.txt` a `/data/paradise/offsets.txt`
3. Reiniciar la consola con GoldHEN activo (el plugin se carga con el juego)
4. Abrir GTA V, entrar a una sesión, y **R1 + D-pad Derecha** abre el menú

Logs: se ven en el log de GoldHEN (`klog`), con prefijo `[paradise]`. Buscá ahí
las líneas `native table discovered at …` y `native layer ready`.

---

## 5. Controles

| botón | acción |
|---|---|
| **R1 + →** | abrir menú (igual que en PS3) |
| ↑ / ↓ | navegar |
| ← / → | cambiar valores (sliders/ints) |
| ✕ (Cross) | seleccionar / togglear |
| ○ (Circle) | volver / cerrar |

Las páginas están en `src/pages.cpp`; `Debug / Native Layer` muestra en pantalla
la dirección de la tabla, cuántos registros encontró y si calibró bien — es la
primera pantalla que hay que mirar en la consola.

---

## 6. Lo que falta para tener el 100 % del menú

El menú original tiene **122 submenús y ~1 400 opciones**. Lo que queda por portar
se parte en dos:

**A) Páginas que sólo llaman natives** (la mayoría). Son trabajo mecánico:

1. copiar el `case` de `prx.cpp` (ej. `case Self_Options:` línea 10743) a una
   función `page_xxx()` en `ps4/src/pages.cpp`
2. agregar el id en `SubmenuId` (`ps4/include/menu.h`) y la entrada en `kPages`
3. las opciones se copian tal cual: `addBoolOption`, `addIntOption`,
   `addSubmenuOption`… tienen la misma firma que en PS3
4. compilar: si un native ya no existe en 1.57, el reporte te dice cuál y con qué
   reemplazarlo

**B) Features que tocan memoria** (~970 líneas entre `prx.cpp`, `Mods.h` y
`Networking.h`). Éstas **no se pudo portar** y necesitan offsets de 1.57:

| feature | por qué no está | qué hace falta |
|---|---|---|
| Modder protection / freeze patches | parchea instrucciones PowerPC en direcciones de PS3 | offsets + patrones de 1.57 |
| Force host / SCTV slots | llama funciones internas del ebuild de PS3 | offsets de 1.57 |
| Money / recovery | validado en el servidor de Rockstar + servicios PSN muertos | no es posible |
| RCE / RTM / "give real mods" | protocolo propio sobre PSN, servidor apagado en 2021 | no es posible |
| Pools de entidades (`entityPool`, `CNetGamePlayer`) | structs de 32 bits con punteros de 32 bits | structs nuevos de 1.57 |

Para ésas está `include/offsets.h` + `/data/paradise/offsets.txt`: se agregan
direcciones o patrones **sin recompilar**. Cuando tengas un offset, se usa así:

```cpp
uint64_t world = offset::get("world");
if (world) { /* ya se puede leer/escribir */ }
```

---

## 7. Estructura

```
ps4/
├── Makefile              build OpenOrbis + GoldHEN (genera .prx)
├── build.sh              todo en uno
├── include/
│   ├── natives_ps4.h     GENERADO: los 4 646 natives en 1.57
│   ├── native_invoker.h  invoker x86-64 (contexto, args, retornos)
│   ├── types_ps4.h       tipos de GTA V 64-bit (reemplazo de types.h)
│   ├── gta_ext.h         natives que en 2015 no existían + helpers de dibujo
│   ├── menu.h            framework (mismas funciones que el PS3)
│   ├── offsets.h         offsets/patrones editables sin recompilar
│   └── platform.h        logging, tiempo, archivos, notificaciones
├── src/
│   ├── main.cpp          entrada GoldHEN (plugin_load) + hilo del menú
│   ├── native_invoker.cpp descubrimiento de la tabla + calibración
│   ├── menu.cpp          dibujo/input/opciones (port de prx.cpp)
│   ├── pages.cpp         páginas de referencia (port de Mods.h)
│   ├── offsets.cpp       lector de offsets + escáner de patrones
│   └── platform.cpp      klog, usleep, archivos, THEFEED
├── sdk/goldhen/          GoldHEN Plugin SDK vendorizado (MIT)
├── hostcheck/            self-test en PC (natives falsos)
├── tools/
│   ├── gen_natives_ps4.py    PS3 Natives.h -> 1.57
│   ├── rewrite_ps3_calls.py  traduce invoke<>(0x32bit) sueltos
│   ├── verify_hashes.py      controla que ningún hash sea inventado
│   └── nativedb/             base gen8 (6 701 natives) usada para mapear
└── docs/PORTING.md       detalle técnico (ABI, tabla, calibración, decisiones)
```

---

## 8. Aviso

Esto es un port de una base pública con fines de preservación/homebrew. Usarlo
online en GTA Online puede hacer que Rockstar banee la cuenta o la consola, y
molesta a otros jugadores. Probá primero en solitario (`Story Mode` o sesión
privada). El autor original del SPRX (gopro_2027) liberó el código aclarando que
"en su estado actual no hace nada"; este port mantiene esa idea: es una base para
que la sigas, no un producto terminado.
