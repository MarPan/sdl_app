#ifndef GEMCONTROLLER_H
#define GEMCONTROLLER_H

#include "statemachine.h"
#include "gemstate.h"

enum GemType {
  GT_BLUE = 0,
  GT_GREEN,
  GT_PURPLE,
  GT_RED,
  GT_YELLOW,
  GT_COUNT
};

class Board;

class GemController : private StateMachine<GemStates::GemState*>
{
public:
  GemController(int x, int y, Board* board);
  ~GemController();
  void setCoords(std::pair<int,int> coords);
  void moveTo(std::pair<int,int> coords);

  // we need those to forward them to m_gem
  void update(float dt);
  void draw();
  bool onClicked();

  void setType(GemType type);
  Board* getBoard();

private:
  Object* m_gem;
  GemType m_type;
  std::pair<int,int> m_logicalCoords;  // remember to call computeDrawingOrign after changing these coords!
  Board* m_pBoard;

  void onGemReachedDestination();
  std::pair<int,int> computePosition(std::pair<int,int> coords);
};

#endif // GEMCONTROLLER_H
