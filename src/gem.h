#ifndef GEM_H
#define GEM_H

#include "object.h"
#include "state.h"
#include "texturemanager.h"
#include "statemachine.h"

class Board;
class GemState;

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

  Gem(int posX, int posY, GemType type, Board* parent);

  void update(float dt);
  void draw();

  void select();

  void setType(GemType type);
  Board* getBoard();

private:
  void init();
  GemType m_type;
  Board* m_pParent;
};

#endif // GEM_H
