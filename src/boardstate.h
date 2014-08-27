#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "utilities.h"
class Board;

namespace BoardStates {

class BoardState
{
public:
  BoardState(Board *board);
  virtual ~BoardState();

  virtual BoardState* onClick( int x, int y);
  virtual void update(float dt);
  virtual void draw();  
protected:
  Coordinates translateToTileCoords(int x, int y);
  Board *m_pBoard;
};

class IdleState : public BoardState
{
public:
  IdleState(Board *board);
  BoardState* onClick(int x, int y);
};

class SelectedState : public BoardState
{
public:
  SelectedState(Board *board);
  BoardState* onClick(int x, int y);
};

class GemsMovingState : public BoardState
{
public:
  GemsMovingState(Board *board);
};


}

#endif // BOARDSTATE_H

