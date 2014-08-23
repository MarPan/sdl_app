#ifndef MULTIPLATFORMSDL_H
#define MULTIPLATFORMSDL_H

#if defined(_WIN32) || defined(_WIN64)
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#endif // MULTIPLATFORMSDL_H
