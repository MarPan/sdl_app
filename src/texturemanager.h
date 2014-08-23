#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "multiplatformSDL.h"
#include <map>

#define theTextureManager TextureManager::getInstance()

class TextureManager
{
public:
  bool load(std::string fileName, std::string id);
  void draw(std::string id, int x, int y, int width, int height);
  void draw(std::string id, const SDL_Rect &rect);
  std::pair<int,int> getSize(std::string id);

  static TextureManager& getInstance();

private:
  std::map<std::string, SDL_Texture*> m_textureMap;

  TextureManager();
  TextureManager(TextureManager const&);
  void operator=(TextureManager const&);
};

#endif // TEXTUREMANAGER_H
