#include "utilities.h"
#include "multiplatformSDL.h"

void logSDLError(std::ostream &os, const std::string &msg)
{
  os << msg << " error: " << SDL_GetError() << std::endl;
}

//SDL_Texture* renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer)
//{
//  TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);

//  SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);

//  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);

//  SDL_FreeSurface(surf);
//  TTF_CloseFont(font);
//  return texture;
//}

