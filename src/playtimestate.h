#ifndef PLAYTIMESTATE_H
#define PLAYTIMESTATE_H

#include "game.h"
#include "gamestate.h"

//class Board;

class PlayTimeState : public GameState
{
public:
  PlayTimeState(Game* game);
  void onClick(int x, int y);

private:
  //Board* m_pBoard;
  Game* game;
};

#endif // PLAYTIMESTATE_H
