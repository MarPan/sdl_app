#ifndef GEMSTATE_H
#define GEMSTATE_H

#include "state.h"
#include "object.h"

class Gem;

class GemState : public State
{
public:
  GemState(Gem *gem);
  virtual void update(float dt) {};
  virtual void draw();
  virtual bool onClicked();
protected:
  Gem* m_gem;
};

class GemIdleState : public GemState
{
public:
  GemIdleState(Gem *gem);
  bool onClicked();
};

class GemSelectedState : public GemState
{
public:
  GemSelectedState(Gem *gem);
  void draw();
private:
  Object m_circle;
  std::string m_circleName;
};

class GemFallingState : public GemState
{
public:
  GemFallingState(Gem *gem) : GemState(gem) {}
};


#endif // GEMSTATE_H
