#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "utilities.h"
class GemController;
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
  virtual void onEnter();
  virtual void onExit();

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
  SelectedState(Board *board, Coordinates selectedGem);
  BoardState* onClick(int x, int y);
  void onExit();
private:
  Coordinates m_selectedGem;
};

class GemsMovingState : public BoardState
{
public:
  GemsMovingState(Board *board);
};


}

#endif // BOARDSTATE_H

