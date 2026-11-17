# ParadiseGTA
This is the visual studio project for Paradise SPRX GTA

Paradise SPRX for GTA V on the PS3 was started by me in the fall of 2015, originally under the project name of 'Limbo.' It was first released as paradise on May 12, 2016. Progress was very rampant in 2016, 2017, and 2018 until april 2019 when I shut down the services for many months. The project was re-released in early 2020 with not many features added over the course of 2020 and 2021, officially shutting down with GTA Online, December 16, 2021.

I learned so much from the experience and knowledge and friends I gained developing paradise, I want to thank everyone involved along the way.

#### Disclaimer
A lot of the code in this is very very messy... Please keep in mind that I was the only one who saw this code over the past 7 years so I was the only one ever intended to read it. With that said, I knew the code flow going on and was able to work with it just fine. It is also worth mentioning that when this project was started I was also a far worse dev than I am today, so some of that horrible code and structure originally was established by a dev who could hardly type C++ at the time.

I also do not take responsibility for what anybody else does with this code. This is all written for GTA V Online PS3 edition which is not available anymore. If any of this stuff causes havoc at the hands of other dev's then that's not my fault because in it's current state as posted here, it does nothing.

#### More Info
You can find other repo's related to this project posted on my github.

---

## Port a PS4 / GoldHEN (GTA V 1.57)

La carpeta [`ps4/`](ps4/) contiene el port de esta base a **nueva generación**:
plugin `.prx` para **GoldHEN en PS4** con GTA V **1.57**.

- Capa de natives PS3 → 1.57 traducida automáticamente: **4 577 de 4 646 (98,5 %)**
  (`ps4/tools/gen_natives_ps4.py`, reporte en `ps4/build/native_report.md`).
- Framework de menú portado con las mismas funciones y el mismo layout.
- 10 páginas de referencia ya funcionando (self, armas, vehículos, teletransporte,
  clima, jugadores, settings, debug…).
- Capa de memoria/offsets para 1.57 vacía a propósito: ver `ps4/docs/PORTING.md`
  §6 para saber qué features necesitan offsets y cuáles no son portables (RCE/RTM,
  recovery).

Build e instalación: ver [`ps4/README.md`](ps4/README.md).

```bash
export OO_PS4_TOOLCHAIN=/ruta/OpenOrbis-PS4-Toolchain
cd ps4 && ./build.sh        # -> build/paradise_gta.prx -> /data/GoldHEN/plugins/
```
