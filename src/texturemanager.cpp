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
  // check if file is already loaded
  if (m_textureMap.count(id)) {
    return false;
  }

  fileName = resourcePath  + fileName;

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

bool TextureManager::loadText(std::string fontName, std::string text, SDL_Color txtColor, int fontSize)
{
  if (m_textureMap.count(text)) {
    return false;
  }
  fontName = resourcePath  + fontName;

  TTF_Font *font = TTF_OpenFont(fontName.c_str(), fontSize);
  if (font == nullptr) {
    std::string err = "Failed to load " + fontName;
    logSDLError(std::cout, err);
    return false;
  }

  SDL_Surface* pTempSurface = TTF_RenderText_Solid(font, text.c_str(), txtColor);
  TTF_CloseFont(font);

  if (pTempSurface == nullptr) {
    std::string err = "Failed to render text " + text;
    logSDLError(std::cout, err);
    return false;
  }

  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(theGame.getRenderer(), pTempSurface);
  SDL_FreeSurface(pTempSurface);
  if (pTexture != nullptr) {
    m_textureMap[text] = pTexture;
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

void TextureManager::draw(std::string id, int x, int y, int width, int height, double angle)
{
  SDL_Rect destRect;
  destRect.w = width;
  destRect.h = height;
  destRect.x = x;
  destRect.y = y;
  draw(id, destRect, angle);
}

void TextureManager::draw(std::string id, const SDL_Rect& rect, double angle)
{
  SDL_Rect srcRect;
  const SDL_Rect &destRect = rect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w;
  srcRect.h = destRect.h;

  int retVal = SDL_RenderCopyEx(theGame.getRenderer(), m_textureMap[id], &srcRect, &destRect, angle, NULL, SDL_FLIP_NONE);
  if (retVal != 0) {
    std::string msg = "Drawing texture " + id + " failed";
    logSDLError(std::cout, msg);
  }
}

TextureManager::~TextureManager()
{
  for (auto& mapPair : m_textureMap) {
    SDL_DestroyTexture(mapPair.second);
  }
}
