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

  void select();

  void setType(GemType type);
  Board* getBoard();

private:
  void init();
  void computeDrawingOrign();
  std::pair<int,int> m_logicalCoords;  // remember to call computeDrawingOrign after changing these coords!
  GemType m_type;
  Board* m_pParent;
};

#endif // GEM_H
