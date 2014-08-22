#ifndef GEM_H
#define GEM_H

#include "object.h"
#include "state.h"
#include "texturemanager.h"
#include "statemachine.h"

class Gem;

class GemState : public State
{
public:
  GemState() {};
  void onEnter(Gem &gem);
  virtual void update(float dt) {};
  virtual void draw();
private:
  Gem* m_gem;
};

class GemIdleState : public GemState
{
public:
  GemIdleState() {}
};

class GemFallingState : public GemState
{
public:
  GemFallingState() {}
};

class Gem : public Object
          , private StateMachine<GemState*>
{
public:
  // or maybe I don't need an enum?
  // I could differentiate between gems based on their m_texId
  // it would be cumbersome to generate random gems though...
  // maybe I should just define somewhere map<GemType, TexId>
  enum GemType {
    GT_BLACK_AND_WHITE = 0,
    GT_BLACK_AND_GREEN,
    GT_BLACK_AND_BLUE,
    GT_BLACK_AND_RED,
    GT_COUNT
  };

  Gem(int posX, int posY, int width, GemType type);

  void update(float dt);
  void draw();

  void setType(GemType type);

private:
  void init();
  GemType m_type;
};

#endif // GEM_H
