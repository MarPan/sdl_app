#ifndef GEMSTATE_H
#define GEMSTATE_H

#include "state.h"
#include "object.h"

class GemController;

namespace GemStates {

class GemState : public State
{
public:
  GemState(Object *gem);
  virtual void update(float dt);
  virtual void draw();
  virtual GemState* onClicked();
protected:
  Object* m_gem;
};

class GemIdleState : public GemState
{
public:
  GemIdleState(Object *gem);
  GemState* onClicked();
};

class GemSelectedState : public GemState
{
public:
  GemSelectedState(Object *gem);
  void draw();
  GemState* onClicked();
private:
  Object m_circle;
  std::string m_circleName;
};

class GemFallingState : public GemState
{
public:
  GemFallingState(Object *gem) : GemState(gem) {}
};

}

#endif // GEMSTATE_H
