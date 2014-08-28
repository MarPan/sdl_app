#ifndef MULTIPLATFORMSDL_H
#define MULTIPLATFORMSDL_H

#include <string>

#if defined(_WIN32) || defined(_WIN64)
  #include <SDL.h>
  #include <SDL_image.h>
  #include <SDL_ttf.h>
  const std::string resourcePath = "..\\..\\resources\\";
#else
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
  #include <SDL2/SDL_ttf.h>
  const std::string resourcePath = "../../resources/";
#endif

#endif // MULTIPLATFORMSDL_H
