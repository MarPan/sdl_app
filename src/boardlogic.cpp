#include "boardlogic.h"

BoardLogic::BoardLogic(int x, int y)
  : m_logicBoard(x, std::vector<GemType>(y))
{
}
