#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "board.h"

class GameState
{
public:
  GameState();
  virtual ~GameState();

  virtual void update(float dt);
  virtual GameState* input(SDL_Event &event);
  virtual void draw();
};

#endif // GAMESTATE_H
