#ifndef MULTIPLATFORMSDL_H
#define MULTIPLATFORMSDL_H

#include <string>

#if defined(_WIN32) || defined(_WIN64)
#include <SDL.h>
#include <SDL_image.h>
const std::string resourcePath = "..\\..\\resources\\";
//const std::string resourcePath = "C:\\Users\\Marek\\Documents\\Programowanie\\C++\\sdl_app\\resources\\";
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
const std::string resourcePath = "../resources/";
#endif

#endif // MULTIPLATFORMSDL_H
