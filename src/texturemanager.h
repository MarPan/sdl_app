#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <map>

#define theTextureManager TextureManager::getInstance()

class TextureManager
{
public:
  bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
  void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer);

  static TextureManager& getInstance();

private:
  std::map<std::string, SDL_Texture*> m_textureMap;

  TextureManager();
  TextureManager(TextureManager const&);
  void operator=(TextureManager const&);
};

#endif // TEXTUREMANAGER_H
