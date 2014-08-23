#ifndef MULTIPLATFORMSDL_H
#define MULTIPLATFORMSDL_H

#if defined(__GNUC__) || defined(__MINGW32__)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#endif // MULTIPLATFORMSDL_H
