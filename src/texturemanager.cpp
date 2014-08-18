#include <SDL2/SDL_image.h>
#include "texturemanager.h"
#include "game.h"

TextureManager::TextureManager()
{ }

/*static*/ TextureManager& TextureManager::getInstance()
{
  static TextureManager instance;
  return instance;
}

bool TextureManager::load(std::string fileName, std::string id)
  {
  // check if file is already loaded
  if (m_textureMap.count(id))
    return false;

  SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
  if (pTempSurface == 0) {
    return false;
  }
  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(theGame.getRenderer(), pTempSurface);
  SDL_FreeSurface(pTempSurface);

  if(pTexture != 0) {
    m_textureMap[id] = pTexture;
    return true;
  }
  return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;
  SDL_RenderCopyEx(theGame.getRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
