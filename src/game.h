#ifndef GAME_H
#define GAME_H

#include "statemachine.h"
#include "multiplatformSDL.h"

#define theGame Game::getInstance()

class GameState;

class Game : private StateMachine<GameState*>
{
public:
  void init(void);
  void run(void);
  ~Game();

  SDL_Renderer* getRenderer() { return m_pRenderer; }

  static Game& getInstance();

private:  
  Game();
  void input();
  void update(float deltaTime);
  void draw();

private:
  std::pair<int, int> _windowSize;
  bool _exit;
  int _lastTime;
  SDL_Window* m_pWindow;                     // holds window properties
  SDL_Renderer* m_pRenderer;                 // holds rendering surface properties
  SDL_Event event;
  SDL_Texture* background;
};

#endif // GAME_H
