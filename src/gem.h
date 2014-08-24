#ifndef GEM_H
#define GEM_H

#include "object.h"
#include "state.h"
#include "texturemanager.h"
#include "statemachine.h"
#include "gemstate.h"

class Board;

class Gem : public Object
          , private StateMachine<GemStates::GemState*>
{
public:
  enum GemType {
    GT_BLUE = 0,
    GT_GREEN,
    GT_PURPLE,
    GT_RED,
    GT_YELLOW,
    GT_COUNT
  };

  Gem(int posX, int posY, GemType type, Board* parent);

  void update(float dt);
  void draw();
  bool onClicked();

  void setType(GemType type);
  Board* getBoard();
  std::pair<int,int> getLogicalCoords();
  void setLogicalCoords(std::pair<int,int> coords);
  void select();

private:
  void init();
  void computeDrawingOrign();
  // ok this is BS, gems shouldn't know this
  // i think
  std::pair<int,int> m_logicalCoords;  // remember to call computeDrawingOrign after changing these coords!
  GemType m_type;
  Board* m_pParent;
};

#endif // GEM_H
