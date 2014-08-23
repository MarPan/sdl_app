#ifndef GEMSTATE_H
#define GEMSTATE_H

#include "state.h"

class Gem;

class GemState : public State
{
public:
  GemState(Gem *gem);
  virtual void update(float dt) {};
  virtual void draw();
private:
  Gem* m_gem;
};

class GemIdleState : public GemState
{
public:
  GemIdleState(Gem *gem) : GemState(gem) {}
};

class GemSelectedState : public GemState
{
public:
  GemSelectedState(Gem *gem);
  void draw();
};

class GemFallingState : public GemState
{
public:
  GemFallingState(Gem *gem) : GemState(gem) {}
};


#endif // GEMSTATE_H
