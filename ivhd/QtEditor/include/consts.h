#ifndef CONSTS_H
#define CONSTS_H

typedef float Real;
#define REAL_HUGE 1e20f

#define APP_VERSION "1.2.1.1"
#define VERSION_DATE "2019-04-17"

#define MAX_DIMENSIONS 10000

#ifndef M_PI
#define M_PI 3.1415926535897932384626433f
#endif

#endif // CONSTS_H


// 1.1.9.3 - jesli wczytany zbior ma <= 3 wymiary, to nie randomizuj, tylko uzyj "Max variance coords"
// 1.2.1.1 - rozdzielenie wersji 2D i 3D (forces, timestep)
//         - dodanie antialiasingu
