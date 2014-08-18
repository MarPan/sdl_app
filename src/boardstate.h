#ifndef BOARDSTATE_H
#define BOARDSTATE_H

class BoardState
{
public:
  virtual ~BoardState() {}
  virtual void handleInput() {}
  virtual void update() {}
};

#endif // BOARDSTATE_H
