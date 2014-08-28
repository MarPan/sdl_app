#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "multiplatformSDL.h"
#include <map>

#define theTextureManager TextureManager::getInstance()

class TextureManager
{
public:
  bool load(std::string fileName, std::string id);
  bool loadTextWithFont(std::string fontName, std::string id, std::string txt, SDL_Color txtColor, int fontSize = 24);
  void draw(std::string id, int x, int y, int width, int height, double angle = 0);
  void draw(std::string id, const SDL_Rect &rect, double angle);
  void drawFont(std::string id, int x, int y);
  std::pair<int,int> getSize(std::string id);

  static TextureManager& getInstance();

private:
  std::map<std::string, SDL_Texture*> m_textureMap;

  TextureManager();
  TextureManager(TextureManager const&);
  void operator=(TextureManager const&);
};

#endif // TEXTUREMANAGER_H
