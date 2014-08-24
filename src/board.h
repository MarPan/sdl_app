#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <map>
#include "object.h"
#include "statemachine.h"
#include "boardstate.h"
#include "boardlogic.h"
#include "gem.h"

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

  void fillBoard();
  std::pair<int,int> func();
  bool swapGems(std::pair<int,int> gemOne,
                std::pair<int,int> gemTwo);

  // @args Logical coords
  void selectGem(int x, int y);

  // Drawing related stuff
  std::pair<int,int> getGemsOffset();
  int getTileWidth();
  std::pair<int,int> getSize();
  std::string getGemPath(Gem::GemType);
  Gem *getGem(int x, int y);
  BoardLogic* getLogic();  // actually after all those changes, I could use a controller, e.g.
  // BoardController, which has both Board(View?) and BoardLogic
  // every update it would poll logic with updateBoard
  // and send the result to BoardView::updateBoard
  // ...naming is not fortunate here

  void setSelectedGem(std::pair<int,int> coords);
  std::pair<int,int> getSelectedGem() const;
  void updateBoard(std::shared_ptr<MoveInfo> moveInfo);


private:
  int m_gemWidth;  //< in pixels
  std::vector<std::vector<Gem*>> m_gems;  //< graphic objects
  std::string m_backgroundPath;  
  std::pair<int,int> m_gemsOffset;  //< draw topleft gem here
  std::pair<int,int> m_size;  //< in rows and columns
  std::map<Gem::GemType, std::string> m_gemRegistry;  //< every gemType has an image resource
  std::pair<int,int> m_selectedGem;
  BoardLogic* m_boardLogic;
};

#endif // BOARD_H
