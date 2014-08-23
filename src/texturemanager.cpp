#include "texturemanager.h"
#include "utilities.h"
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
  fileName = resourcePath  + fileName;
  std::cout << fileName << std::endl;
  // check if file is already loaded
  if (m_textureMap.count(id))
    return false;

  SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
  if (pTempSurface == 0) {
    std::cout << "Failed to load " << fileName << std::endl;
    logSDLError(std::cout, "");
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

std::pair<int,int> TextureManager::getSize(std::string id)
{
  std::pair<int,int> retVal(0,0);
  int error = 0;
  if (m_textureMap.count(id)) {
    error = SDL_QueryTexture(m_textureMap[id], NULL, NULL, &retVal.first, &retVal.second);
  }

  if (error) {
    logSDLError(std::cout, "Failed to query texture.");
  }
  return retVal;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height)
{
  SDL_Rect destRect;
  destRect.w = width;
  destRect.h = height;
  destRect.x = x;
  destRect.y = y;
  draw(id, destRect);
}

void TextureManager::draw(std::string id, const SDL_Rect& rect)
{
  SDL_Rect srcRect;
  const SDL_Rect &destRect = rect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w;
  srcRect.h = destRect.h;

  int retVal = SDL_RenderCopyEx(theGame.getRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
  if (retVal != 0) {
    std::string msg = "Drawing texture " + id + " failed";
    logSDLError(std::cout, msg);
  }
}
