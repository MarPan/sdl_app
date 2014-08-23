#ifndef BOARDSTATE_H
#define BOARDSTATE_H

class Board;

class BoardState
{
public:
  BoardState();
  virtual ~BoardState();

  virtual void onClick( int x, int y) = 0;
  virtual void update(float dt) = 0;
  virtual void draw() = 0;
};

class IdleState : public BoardState
{
public:
  IdleState(Board *board);
  void onClick(int x, int y);
  void update(float dt);
  void draw();
private:
  Board *m_pBoard;  // TODO: is this a good idea? maybe we coud move it to BoardStae.
};









#endif // BOARDSTATE_H

