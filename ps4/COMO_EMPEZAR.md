# Cómo empezar (sin saber nada de mod menus)

Esta guía es para alguien que nunca tocó un mod menu en PS4. Sin vueltas.

---

## ¿Qué es lo que tenés?

Dos cosas:

1. **La base original de PS3** (`ParadiseGTA_optimized_2020/`): el proyecto del menú
   que se usaba en PS3. Esa carpeta ya no se toca, queda como referencia.
2. **El port para PS4** (`ps4/`): la versión de nueva generación, que se convierte
   en un archivo llamado `paradise_gta.prx`.

Un **`.prx`** es simplemente "el archivo del mod": es lo que la consola carga
cuando abre el juego. No se instala como un juego, se copia en una carpeta.

---

## Lo que tenés que tener antes

| cosa | qué es |
|---|---|
| **PS4 con GoldHEN** | GoldHEN es el "jailbreak" de PS4. Sin eso no se puede cargar ningún `.prx`. Si tu consola no lo tiene, este proyecto no sirve todavía. |
| **GTA V versión 1.57** | la versión del juego para la que está hecho el port. |
| **Una PC** | para compilar (ver abajo) y para copiar el archivo a la consola. |
| **El compilador de PS4** | se llama **OpenOrbis PS4 Toolchain**. Es gratis. |

---

## Los 3 pasos

### Paso 1 — Compilar (convertir el proyecto en el archivo `.prx`)

**Yo no pude generarte el `.prx` ya hecho**: en el entorno donde trabajo no hay
compilador de PS4 y la descarga del compilador está bloqueada. Así que hay que
compilarlo en tu PC (una sola vez, tarda pocos minutos).

Necesitás dos cosas:

| cosa | dónde |
|---|---|
| **OpenOrbis PS4 Toolchain** | https://github.com/OpenOrbis/OpenOrbis-PS4-Toolchain/releases (v0.5.4 este caso) |
| **clang + make + python** | en Windows se instalan con MSYS2 (abajo) |

#### Ruta A — Windows (la que usa la mayoría)

1. Instalar **MSYS2**: https://www.msys2.org (siguiente, siguiente, finalizar).
2. Abrir del menú Inicio **"MSYS2 MINGW64"** (esa ventana, no otra) y pegar:

   ```bash
   pacman -S --needed --noconfirm mingw-w64-x86_64-clang mingw-w64-x86_64-lld make python dos2unix
   ```

3. Copiar el proyecto a tu carpeta de usuario (más rápido que compilar sobre `F:`)
   y limpiar los finales de línea que agrega Windows:

   ```bash
   cp -r /f/ps4 ~/ps4
   cd ~/ps4
   dos2unix Makefile build.sh hostcheck/Makefile
   ```

4. Compilar, apuntando al toolchain (con **barra normal**, `F:/...`, no `F:\...`):

   ```bash
   export OO_PS4_TOOLCHAIN=F:/OpenOrbis/PS4Toolchain
   make
   ```

   El Makefile detecta solo que está en Windows y usa `bin/windows/create-fself.exe`.
   (Si alguna vez hace falta forzarlo: `make CDIR=windows`.)

Si todo sale bien, termina con:

```
built build/paradise_gta.prx
```

y el archivo queda en `~/ps4/build/paradise_gta.prx`. Para pasarlo a Windows:

```bash
cp build/paradise_gta.prx /f/
```

#### Ruta B — Linux o WSL

```bash
export OO_PS4_TOOLCHAIN=/ruta/al/OpenOrbis-PS4-Toolchain
cd ps4
./build.sh          # regenera natives (si está el árbol de PS3) + verifica hashes + compila
```

#### Si algo falla en este paso

| mensaje | qué hacer |
|---|---|
| `You must install .NET` | `create-fself.exe` es un programa .NET: instalá el **.NET Runtime 8** desde dotnet.microsoft.com y repetí el `make` |
| `ERROR: OO_PS4_TOOLCHAIN is not set` | falta el `export` en esa misma ventana |
| `ERROR: .../link.x not found` | `OO_PS4_TOOLCHAIN` tiene que apuntar a la carpeta que contiene `link.x`, `include`, `lib` y `bin` |
| `clang: command not found` | ventana equivocada: usá **MSYS2 MINGW64** y repetí el `pacman` |
| `bad interpreter: ...^M` | finales de línea de Windows: `dos2unix Makefile build.sh` |

> Si aparece cualquier otro error, mandame las últimas 20 líneas del texto y lo
> miramos juntos. Es el paso donde más gente se traba y no es tu culpa.

### Paso 2 — Copiar el archivo a la PS4

1. Conectá un pendrive a la PS4 (o usá FTP).
2. Copiá `paradise_gta.prx` a la carpeta:

   ```
   /data/GoldHEN/plugins/
   ```

   (si la carpeta `plugins` no existe dentro de `/data/GoldHEN/`, creala)
3. Reiniciá la consola con GoldHEN activo.

### Paso 3 — Abrirlo en el juego

1. Abrí GTA V y entrá al mundo (modo historia o una sesión).
2. Apretá **R1 + D-pad Derecha** al mismo tiempo.
3. Aparece el menú.

---

## ¿Cómo sé si funcionó?

- **Se ve el menú** → funcionó. Andá a la página **Debug / Native Layer**: ahí te
  muestra si encontró la tabla del juego y si está todo bien calibrado.
- **No pasa nada al apretar R1+Derecha** → mirá el log de GoldHEN (el menú de
  GoldHEN tiene una opción para ver el log). Buscá las líneas que empiezan con
  `[paradise]`. Las más importantes:

  | línea en el log | qué significa |
  |---|---|
  | `native table discovered at 0x…` | encontró la tabla del juego, va bien |
  | `native layer ready (… calibrated)` | está todo listo |
  | `calibration failed` | encontró la tabla pero el juego respondió distinto (build distinta) |
  | `native table not found` | no la encontró; hay que darle una pista (ver `offsets.example.txt`) |
  | `giving up: native layer unavailable` | no arrancó; no va a andar hasta arreglar lo de arriba |

---

## Qué trae hoy (y qué no)

**Trae:** el menú funcionando con 10 páginas: Self Options, Armas, Vehículos,
Players, Teleport, Clima/Hora, Lobby, Settings y Debug.

**No trae todavía:**

- **El resto de las páginas** del menú original (tenía 122 submenús y ~1.400
  opciones). La mayoría son copiar y pegar mecánico, está explicado en
  `docs/PORTING.md`.
- **Las opciones que tocan la memoria del juego** (protección anti-modder, freeze,
  force host, money/recovery, RCE/RTM). Esas necesitan "offsets" de la versión 1.57
  que no están en el proyecto original de PS3 porque eran de 32 bits. No es que no
  se pueda: es que hay que sacarlos con ingeniería inversa de la versión de PS4.
- **RCE / RTM / "give real mods"**: eso usaba un servidor del autor que se cerró en
  diciembre de 2021. No hay forma de que funcione hoy, ni en PS3.

Es decir: **es una base que funciona y está lista para que la sigas**, no el menú
completo de 1.400 opciones.

---

## Glosario mínimo

| palabra | significado |
|---|---|
| **GoldHEN** | el jailbreak de PS4. Permite correr cosas que Sony no deja. |
| **PRX** | el archivo del mod (como un `.dll` en Windows). |
| **Plugin** | un PRX que GoldHEN carga automáticamente al abrir el juego. |
| **Native** | una función interna del juego ("dar vida", "crear vehículo"). El menú las llama por un número (hash). |
| **Hash** | ese número que identifica cada native. En PS3 y en PS4 son distintos, y ahí estaba el trabajo principal. |
| **Offset** | una dirección de memoria del juego. Cambia en cada versión. |
| **klog / log** | el "diario" donde el plugin escribe qué está haciendo, para poder diagnosticar. |
| **1.57** | la versión de GTA V de PS4 para la que está hecho todo esto. |
