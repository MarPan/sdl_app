#include "boardlogic.h"

BoardLogic::BoardLogic(int x, int y)
  : m_logicBoard(x, std::vector<GemType>(y))
{
}

void BoardLogic::swapGems(Coordinates src, Coordinates dst, MoveInfo& moveInfo)
{
  moveInfo.addInvalidSwap(InvalidSwap(src, dst));
}

void BoardLogic::updateBoard(MoveInfo& moveInfo)
{

}
