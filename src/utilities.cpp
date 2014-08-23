#include "utilities.h"
#include "multiplatformSDL.h"

void logSDLError(std::ostream &os, const std::string &msg)
{
  os << msg << " error: " << SDL_GetError() << std::endl;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip)
{
  SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip)
{
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  if (clip != nullptr) {
    dst.w = clip->w;
    dst.h = clip->h;
  } else {
    SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
  }

  renderTexture(tex, ren, dst, clip);
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

