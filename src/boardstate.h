#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "state.h"

class BoardState : public State
{
public:
  virtual ~BoardState() {}
  virtual void handleInput() {}
  virtual void update() {}
};

#endif // BOARDSTATE_H
