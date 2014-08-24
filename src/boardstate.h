#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include <utility>

class Board;

namespace BoardStates {

class BoardState
{
public:
  BoardState(Board *board);
  virtual ~BoardState();

  virtual BoardState* onClick( int x, int y) = 0;
  virtual void update(float dt);
  virtual void draw();  
protected:
  std::pair<int,int> translateToTileCoords(int x, int y);
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

}

#endif // BOARDSTATE_H

