#include "boardlogic.h"

BoardLogic::BoardLogic(int x, int y)
  : m_logicBoard(x, std::vector<GemType>(y))
{
}

void BoardLogic::swapGems(Coordinates src, Coordinates dst, MoveInfo& moveInfo)
{
  std::cout << "Src: " << coordsToString(src) << std::endl;
//  moveInfo.addInvalidSwap(InvalidSwap(src, dst));
  moveInfo.addAnnihilation(src);
  return;
  moveInfo.addInvalidSwap(InvalidSwap(src, dst));
  moveInfo.addInvalidSwap(InvalidSwap(src, dst));
  return;

  int random = rand()%2;
  switch (random) {
    case 0:
      moveInfo.addInvalidSwap(InvalidSwap(src, dst));
      break;
    case 1:
      moveInfo.addRelocation(Relocation(src, dst));
      moveInfo.addRelocation(Relocation(dst, src));
      break;
    }
}

bool BoardLogic::isMovePossible(Coordinates src, Coordinates dst)
{
  auto copy = m_logicBoard;
  std::swap(copy[src.first][src.second], copy[dst.first][dst.second]);
  MoveInfo moveInfo;
  return findConnections(copy, moveInfo);
}

// scans the board. If finds connection, adds moves to the moveInfo:
// Annihilation for the gems from connection
// Relocation for the gems over the connection
// TODO: what should we do when we have more than two connections?
// SOLUTION: we should do it in steps: firstly, remove all of the connections
// then let all the pieces fall to their new positions - one tile at a time!
bool BoardLogic::findConnections(const std::vector<std::vector<GemType>>& logicBoard, MoveInfo& moveInfo)
{

}

void BoardLogic::updateBoard(MoveInfo& moveInfo)
{
  std::cout << "BoardLogic tick!" << std::endl;
}
