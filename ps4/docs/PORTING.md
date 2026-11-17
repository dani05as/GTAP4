# Detalle técnico del port PS3 → PS4 (GTA V 1.57, GoldHEN)

Documento de referencia de **cómo** se hizo el port, decisión por decisión. Sirve
para seguir portando el resto del menú y para entender por qué algunas cosas no
se pueden portar.

---

## 1. El problema, en números

| | PS3 SPRX | PS4 GoldHEN |
|---|---|---|
| CPU | Cell PPU (PowerPC), 2 hilos efectivos | x86-64, 6 hilos del juego |
| Punteros | 32 bits | 48 bits útiles |
| Endianness | big | little |
| Hash de native | `joaat32(nombre_minúsculas)` | 64 bits (tabla gen8) |
| Argumento de native | 4 bytes en `0x10050000` | 8 bytes, array propio |
| Tabla de natives | global en el ebuild (`0x1E6FF38`) | global en el ebuild de 1.57 (desconocida) |
| Llamada a native | `NativeFunctions[i](&arg)` con OPD | `handler(&ctx)` x86-64 |
| Hilos | `sys_ppu_thread_create` | `sceKernelCreateThread` |
| Archivos | `cellFs*` | stdio (musl de OpenOrbis) |
| Pad | `cellPadGetData` | natives `CONTROLS::*` |
| Diálogos | `sysutil` (msg/osk dialog) | THEFEED nativo |
| Texto/dibujo | natives `UI::/GRAPHICS::` | **los mismos**, otros hashes |
| Direcciones de juego | descargadas (`addrstruct()`) | hay que descubrirlas |
| Servicios | PSN + servidor propio | muertos desde 2021 |

De ahí sale la regla del port:

> **se reutiliza todo lo que pasa por natives; se reescribe todo lo que toca
> memoria o servicios.**

---

## 2. La capa de natives

### 2.1 Por qué el hash no sirve como puente

```c
joaat32("GET_PLAYER_PED") == 0x6E31E993        // PS3
                     PS4 == 0x43A66C31C68491C0 // 64 bits, otro algoritmo
```

No hay transformación entre ambos. Se mapea por **identidad**:

1. `jhash` de la base gen8 == hash de PS3 ⇒ mismo native, mismo nombre.
   Resuelve **4 569** de 4 646 (incluye ~1 969 que el header de 2015 sólo conoce
   como `_0xDEADBEEF`: Rockstar nunca cambió el hash, así que aparecen en la base
   moderna con su nombre real).
2. Si el nombre cambió pero el hash no, (1) ya lo resuelve.
3. Si cambió el *nombre* y el *hash* (renombres de 2017 que además cambiaron la
   cadena), se resuelve por nombre con la tabla `RENAME_OVERRIDES` del generador.
4. Lo que no aparece en ninguno: **stub seguro** (compila, loguea una vez, devuelve 0).

### 2.2 Firma: se conserva la de 2015

El generador emite **la firma del header de PS3** (no la moderna). Motivo: los
call sites de `Mods.h`/`prx.cpp` están escritos contra esa firma. Cambiar la firma
obligaría a editar 21 000 líneas a mano.

Pero se aplican tres correcciones automáticas, porque el ABI de 64 bits lo exige:

| caso | ejemplo | qué genera |
|---|---|---|
| handle por puntero en PS3, por valor en PS4 | `DELETE_ENTITY(Entity*)` | `*param` |
| parámetro nuevo al final en 1.57 | `DRAW_RECT` ganó un `BOOL` | rellena con `0` |
| parámetros que ya no existen | varias firmas viejas con extras | los descarta |
| nombre de parámetro que tapa un tipo | `GET_ENTITY_ATTACHED_TO(Entity Entity)` | lo renombra a `entity` |

Todo queda listado en `build/native_report.md`.

### 2.3 El invoker (x86-64)

`include/native_invoker.h`, traducción del `nativeCaller.h` de PS3:

```cpp
// PS3
struct Native_s { Native_s* LastNativesTable; unsigned int NativeFunctions[7];
                  unsigned int NativeCount;    unsigned int NativeHashes[7]; };

// PS4
struct Registration { Registration* next; void* handlers[7];
                      uint32_t numEntries1, numEntries2; uint64_t hashes[7]; };
static_assert(sizeof(Registration) == 0x80);
```

`invoke_native<Ret>(hash, args...)`:
- cada argumento ocupa **un slot de 8 bytes** (`g_args`);
- enteros se extienden con signo (o cero si son unsigned), `float` va en los 4
  bytes bajos del slot, `char*`/punteros van completos;
- `Vector3` se pasa **por puntero** (como en gen8), con un pool estático porque el
  hilo del menú es el único que llama;
- el retorno se lee de `g_ret` (64 bytes, alcanza para `Vector3` y structs chicos);
- hay una caché directa hash→handler de 1 024 entradas: el menú dispara ~200
  natives por frame y no conviene recorrer cadenas cada vez.

### 2.4 Encontrar la tabla de 1.57 sin offsets

`src/native_invoker.cpp`. El PS3 leía `nativeTable` de su servidor; acá no existe,
y hardcodear una dirección rompe en el próximo parche. Así que se **descubre y se
valida**:

1. `sys_sdk_proc_info()` (GoldHEN) da la base del módulo del juego; de su header
   ELF se sacan los rangos `PT_LOAD`.
2. Se busca en esos rangos un `qword` igual a un **canario**: el hash de
   `GET_PLAYER_PED` (`0x43A66C31C68491C0`), que existe desde 2013.
3. Ese qword está dentro de un `scrNativeRegistration`; probando los 7 offsets
   posibles de `hashes[]` se identifica el registro y se valida su forma
   (`numEntries1 == numEntries2 <= 7`, handlers alineados).
4. Se busca en el módulo un qword que apunte a ese registro; si está en la
   posición `p` de la tabla, entonces `tabla = p - 8 * (hash & 0xFF)`.
5. Se **valida la tabla entera**: para cada bucket no nulo, toda la cadena tiene
   que compartir el índice de bucket en su byte bajo, y el total tiene que dar una
   cantidad razonable de registros/natives. Un array cualquiera de punteros no pasa.

### 2.5 Calibración del contexto (sin adivinar)

El layout de `scrNativeCallContext` puede cambiar entre firmwares/builds. En vez de
confiar, se **prueba**:

```
GET_HASH_KEY("weapon_pistol") debe devolver 0x1B06D571
```

Es un native puro, sin estado, cuyo resultado es una constante conocida. Si esa
llamada da el valor esperado, quedan probados de una sola vez: la tabla, el
layout del contexto, el pasaje de argumentos y la lectura del retorno. Si falla,
el plugin **no habilita el menú** y loguea el motivo (`calibration failed: …`).

---

## 3. El menú

`src/menu.cpp` es un port fiel del framework de `prx.cpp`:

- mismos globales (`currentOption`, `optionCount`, `numberofoptions`, `maxOptions`,
  `submenu`, `submenuLevel`, `lastSubmenu[]`, `lastOption[]`, `optionPress`,
  `triggerScrollUp/Down`, `infoText`, colores, `menuYCoord`, `textHeight` 0.035,
  `optionsFont` 4, `bannerTextFont` 1, `minimumMenuWidth` 0.20…);
- mismas funciones (`addTitle`, `addOption`, `addOptionWithRightwardText`,
  `addSubmenuOption`, `addBoolOption`, `addIntOption`, `addFloatOption`,
  `addStrOption`, `addSpacer`, `addOptionIcon`, `addInstruction*`, `updateMenuWidth`,
  `getTextWidth`, `drawText`, `changeSubmenu`, `playSound`);
- mismo layout: banner `// Título`, contador `n/total`, marcador `>` en la opción
  actual, caja de info abajo, barra de scroll cuando hay más de `maxOptions`.

Cambios obligados por la plataforma:

| PS3 | PS4 |
|---|---|
| `*(unsigned int*)0x22147C8` (ancho de pantalla) | `GET_ACTUAL_SCREEN_RESOLUTION` |
| `cellPadGetData` | `CONTROLS::IS_CONTROL_PRESSED/JUST_PRESSED/GET_CONTROL_VALUE` |
| `CellPad` + `GetKey()` | mismos índices frontend (0xC1 accept, 0xC3 cancel, 0xCA..0xCD dpad) |
| `sys_timer_usleep` | `sceKernelUsleep` |
| `sysutil` msg dialog | THEFEED (`BEGIN/END_TEXT_COMMAND_THEFEED_POST*`) |
| `drawing::DrawSprite` (RPF propio) | `GRAPHICS::DRAW_SPRITE` (banner liso) |

El `DRAW_RECT`/`DRAW_SPRITE` de 1.57 tienen un `BOOL` extra al final (ver
`gta_ext.h`), por eso esos dos van por hash explícito y no por el header generado.

### Input: por qué los índices no cambian

Los índices que usa el código (`0xC1`, `0xC3`, `0xCA`…) **no son botones de
hardware**: son acciones frontend de Rockstar (`INPUT_FRONTEND_ACCEPT`,
`INPUT_FRONTEND_CANCEL`, `INPUT_FRONTEND_UP`…), idénticas en PS3, PS4 y PC. Por eso
`CONTROLS::IS_CONTROL_PRESSED(0, 0xC1)` funciona igual en las dos consolas.

---

## 4. Ciclo de vida del plugin

```
plugin_load()                      (GoldHEN, al cargar el .prx en el juego)
 ├─ offset::load_config()          /data/paradise/offsets.txt (opcional)
 ├─ native::init()                 descubrimiento + calibración (reintenta 30×)
 ├─ menu_init()                    páginas + resolución de pantalla
 └─ sceKernelCreateThread(paradise_loop)
      bucle a ~60 fps:
        └─ si PLAYER_PED_ID() != 0:
             pages_tick()   → toggles que aplican aunque el menú esté cerrado
             menu_tick()    → input + draw_menu() → menú
plugin_unload()                    baja el flag del bucle
```

El PS3 hacía lo mismo con `sys_ppu_thread_create` y tres hilos (menú, RTM, RCE);
acá alcanza con uno: el menú. Los otros dos eran para servicios que ya no existen.

---

## 5. Portar una página nueva (receta)

Ejemplo real: `Self Options`.

1. en `prx.cpp` está el `case`:
   ```cpp
   case Self_Options:
       addTitle(getCachedString("STR17"));
       addBoolOption(getCachedString("STR18"), &godmode, ...);
       ...
   ```
2. en `ps4/src/pages.cpp`:
   ```cpp
   void page_self() {
       addBoolOption((char*)"Godmode", &godmode, (char*)"Invincible player");
       ...
   }
   ```
3. registrar en `kPages` y en `SubmenuId` (`include/menu.h`).
4. si el `case` original usaba `*(volatile ...*)0x...` o `addrstruct()`, esa parte
   **no se copia**: se deja detrás de un `if (uint64_t a = offset::get("clave"))`.

Para copiar en masa, `tools/rewrite_ps3_calls.py` traduce los `invoke<>(0x32bit)`
sueltos y reescribe los `#include`:

```bash
python3 tools/rewrite_ps3_calls.py \
    --in ../../ParadiseGTA_optimized_2020/prx.cpp \
    --map build/native_hash_map.json --out build/prx.ported.cpp
```

Ojo: en esta base **casi no hay `invoke` crudos** (1 en `prx.cpp`, 4 en
`Scaleforms.h`); el resto pasa por los nombres de `Natives.h`, que ya están
traducidos. Es decir, el trabajo pesado del port **no** es la capa de natives: es
separar las features de memoria de las que sólo llaman natives.

---

## 6. Lo que no se puede portar, y por qué

| bloque | líneas aprox. | motivo técnico |
|---|---|---|
| `addrstruct()` + `dataDecryptor()` (`Networking.h`) | ~200 | tabla de 24 offsets de 32 bits del ebuild de PS3, entregada por el servidor del autor. En PS4 no existe; cada offset hay que sacarlo con IDA/Ghidra sobre el ebull de 1.57 |
| Protección anti-modder, freeze, proofs | ~400 | parchea instrucciones **PowerPC** (`0x4BB33C79`, `0x41820030`…) en direcciones de PS3 |
| Pools de entidades / `CNetGamePlayer` / `CPlayerInfo` | ~300 | structs con punteros de 32 bits y offsets propios del build de PS3 |
| RCE / RTM / "give real mods" | ~1 200 | protocolo propio sobre PSN; servidor apagado en dic-2021 |
| Money / recovery / RP | ~500 | validado del lado del servidor de Rockstar |
| `HEN_MODE`, cifrado `findAndDecrypt`, anti-tamper | ~800 | protecciones del SPRX; GoldHEN carga PRX sin firmar, no hacen falta |
| `Scaleforms.h` "phone menu" 3D | ~500 | usa el móvil del juego + texturas del RPF de PS3; se puede rehacer con scaleforms nativos, no es prioritario |

Los offsets que sí quieras usar van a `/data/paradise/offsets.txt` (ver
`offsets.example.txt`), sin recompilar.

---

## 7. Cómo se validó (y qué falta)

**Validado en este repo:**

- `tools/verify_hashes.py`: los 84 hashes de 64 bits escritos a mano existen en la
  base gen8 (0 desconocidos). Esto detectó, por ejemplo, que el hash que estaba
  puesto para `GET_CONTROL_VALUE` no existía (un dígito cambiado = native
  equivocado, silencioso en consola).
- `hostcheck/`: el mismo `menu.cpp`, `pages.cpp`, `native_invoker.cpp` y
  `offsets.cpp` compilados para PC con un **PS4 falso** (natives que registran las
  llamadas). El test abre el menú con R1+→, entra a las 10 páginas, togglea
  opciones, scrollea hasta el fondo, valida el clamping y cierra: **0 fallos,
  31 929 llamadas de native despachadas**, y el texto que dibujaría el menú sale
  impreso. Eso prueba el framework, el marshalling de argumentos y la lógica de
  páginas.
- El `Makefile` sigue exactamente el patrón oficial del GoldHEN Plugins SDK
  (`crtprx.o`, `-e _init`, `create-fself --paid 0x3800000000000011`).

**Falta (necesita consola):**

1. `TODO(consola)` `native::discover()` — que el canario aparezca en el .data de
   tu 1.57 y la validación acepte la tabla. Si falla: `pattern.native_table` en el
   config o `native_table` a mano; el log dice exactamente en qué paso se quedó.
2. `TODO(consola)` calibración del contexto (debería pasar; si no, el log imprime
   qué devolvió `GET_HASH_KEY`).
3. `TODO(consola)` dibujado desde el hilo del plugin: que el juego lo componga
   encima del HUD. Si no se ve, el orden de `SET_SCRIPT_GFX_DRAW_ORDER` es lo
   primero a revisar.
4. Los offsets de 1.57 para §6.

Cada uno de esos puntos tiene su log; en la consola, la página
**Debug / Native Layer** del menú muestra tabla, módulo, registros, natives y si
calibró.
