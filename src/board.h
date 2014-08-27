#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <map>
#include "object.h"
#include "statemachine.h"
#include "boardstate.h"
#include "gemcontroller.h"
#include "moveinfo.h"

class Gem;
class BoardLogic;

class Board : public Object
            , public StateMachine<BoardStates::BoardState*>
{
public:
  Board(int rows, int cols);
  ~Board();

  void update(float dt);
  void draw();
  void onClick(int x, int y);

  bool swapGems(Coordinates gemOne,
                Coordinates gemTwo);

  // @args Logical coords
  void selectGem(int x, int y);

  // Drawing related stuff
  Coordinates getGemsOffset();
  int getTileWidth();
  Coordinates getSize();
  std::string getGemPath(GemType);
  bool clickGem(int x, int y);

  void setSelectedGem(Coordinates coords);
  Coordinates getSelectedGem() const;
  void gemFinishedMoving(GemController *gem);

private:
  Coordinates m_size;
  std::string m_backgroundPath;
  int m_gemWidth;
  std::vector<std::vector<GemController*>> m_gems;
  Coordinates m_gemsOffset;
  std::map<GemType, std::string> m_gemRegistry;
  Coordinates m_selectedGem;
  BoardLogic *m_boardLogic;

  std::vector<GemController*> m_gemsInMotion;

  void parseMoveInfo(const MoveInfo& moveInfo);
};

#endif // BOARD_H
