#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "object.h"
#include "statemachine.h"
#include "boardstate.h"

class Gem;
class BoardLogic;

// I need to have BoardView and BoardModel/Logic
// or sth like this.
// oh would you look at that
// https://github.com/yoavfrancis/Bejeweled

/*
 * So this guy has done a really nice job: he has a
 * GameBoard,which consists of BoardView (draws) and BoardLogic (updates).
 * He only has "states" based on enums, and no states for gems.
 * He doesn't have animations
 *
 * Also, in his implementation BV and BM didn't have to be separate - but
 * it really seems smoother that way. Also because in my implementation, I will change
 * gems in BoardModel at once, but Gems in BoardModel will have m_destination, to which
 * they will slide
 *
 * So, in fact, BoardModel won't have gems - only an array of GemTypes, that should be enough.
 *
 * We do need some way of connecting a Gem to a graphic object
 */
class Board : public Object
            , public StateMachine<BoardState*>
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

  std::pair<int, int> size;

private:
  int m_tileWidth;
  std::vector<std::vector<Gem*>> m_gems;  
  std::string m_backgroundPath;
};

#endif // BOARD_H
