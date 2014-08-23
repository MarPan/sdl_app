#ifndef PLAYTIMESTATE_H
#define PLAYTIMESTATE_H

#include "board.h"
#include "gamestate.h"

//class Board;

class PlayTimeState : public GameState
{
public:
  PlayTimeState();
  void onClick(int x, int y);
  void update(float dt);
  void draw();

private:
  Board* m_pBoard;
};

#endif // PLAYTIMESTATE_H