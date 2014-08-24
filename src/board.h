#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <map>
#include "object.h"
#include "statemachine.h"
#include "boardstate.h"
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

  void setSelectedGem(std::pair<int,int> coords);
  std::pair<int,int> getSelectedGem() const;

private:
  int m_gemWidth;
  std::vector<std::vector<Gem*>> m_gems;  
  std::string m_backgroundPath;
  std::pair<int,int> m_gemsOffset;
  std::pair<int,int> m_size;
  std::map<Gem::GemType, std::string> m_gemRegistry;
  std::pair<int,int> m_selectedGem;
};

#endif // BOARD_H
