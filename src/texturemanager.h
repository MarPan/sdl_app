#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include "multiplatformSDL.h"

#define theTextureManager TextureManager::getInstance()

class TextureManager
{
public:
  ~TextureManager();
  bool load(std::string fileName, std::string id);
  bool loadText(std::string fontName, std::string text, SDL_Color txtColor, int fontSize);
  void draw(std::string id, int x, int y, int width, int height, double angle = 0);
  void draw(std::string id, const SDL_Rect &rect, double angle);
  std::pair<int,int> getSize(std::string id);

  static TextureManager& getInstance();

private:
  std::map<std::string, SDL_Texture*> m_textureMap;

  TextureManager();
  TextureManager(TextureManager const&);
  void operator=(TextureManager const&);
};

#endif // TEXTUREMANAGER_H
