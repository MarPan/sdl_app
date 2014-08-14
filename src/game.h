#ifndef GAME_H
#define GAME_H

#include <world.h>
#include <SDL2/SDL.h>

class Game
{
public:
  Game();

  void init(void);
  void run(void);

private:
  void input();
  void update(float deltaTime);
  void draw();

private:
  World *_world;
  int _lastTime;
  bool _exit;
  std::pair<int, int> _windowSize;
  SDL_Window* window;                     // holds window properties
  SDL_Renderer* _renderer;                 // holds rendering surface properties
  SDL_Event event;
  SDL_Texture* background;
};

#endif // GAME_H
