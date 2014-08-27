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
  GT_COUNT,
  GT_INVALID
};

class Board;

class GemController : private StateMachine<GemStates::GemState*>
{
public:
  GemController(int x, int y, Board* board);
  ~GemController();
  void setCoords(Coordinates coords);
  void addMoveTo(Coordinates coords);
  void setRotation(double angle, double speed);

  // we need those to forward them to m_gem
  void update(float dt);
  void draw();
  bool onClicked();
  bool isSelected();

  void remove();
  void setType(GemType type);
  GemType getType() { return m_type; }
  Board* getBoard();
  Coordinates getCoordinates();
  bool isRemoved();

private:
  Object* m_gem;
  GemType m_type;
  Coordinates m_logicalCoords;  // remember to call computeDrawingOrign after changing these coords!
  Board* m_pBoard;
  // this flag disables rendering.
  bool m_removed;

  void onGemReachedDestination();
  void onGemFinishedRotation();
  Coordinates computePosition(Coordinates coords);
};

#endif // GEMCONTROLLER_H
