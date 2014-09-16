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

  // Drawing related stuff
  Coordinates getGemsOffset();
  int getTileWidth();
  Coordinates getSize();
  std::string getGemPath(GemType);

  // @args Logical coords
  void deselectGem(Coordinates gem);
  bool clickGem(int x, int y);

  int getPoints() const;
  void gemFinishedMoving(GemController *gem);

private:
  Coordinates m_size;
  int m_gemWidth;
  std::vector<std::vector<GemController*>> m_gems;
  Coordinates m_gemsOffset;
  std::map<GemType, std::string> m_gemRegistry;
  std::vector<Coordinates> m_gemsToBeRemoved;
  BoardLogic *m_boardLogic;
  std::string m_Time;

  std::vector<GemController*> m_gemsInMotion;

  std::string m_invalidMoveSfx;
  std::string m_gemsRemovedSfx;
  std::string m_gemFellSfx;

  void parseMoveInfo(const MoveInfo& moveInfo);
  inline void setState(const state_type& state) override;
};

#endif // BOARD_H
