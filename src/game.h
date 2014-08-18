#ifndef GAME_H
#define GAME_H

#include <world.h>
#include <SDL2/SDL.h>

#define theGame Game::getInstance()

class Game
{
public:

  void init(void);
  void run(void);

  SDL_Renderer* getRenderer() { return m_pRenderer; }

  static Game& getInstance();

private:  
  Game();
  void input();
  void update(float deltaTime);
  void draw();

private:
  World *_world;
  int _lastTime;
  bool _exit;
  std::pair<int, int> _windowSize;
  SDL_Window* m_pWindow;                     // holds window properties
  SDL_Renderer* m_pRenderer;                 // holds rendering surface properties
  SDL_Event event;
  SDL_Texture* background;
};

#endif // GAME_H
