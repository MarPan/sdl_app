#include "boardlogic.h"

BoardLogic::BoardLogic(int x, int y)
  : m_logicBoard(x, std::vector<GemType>(y))
{
}

void BoardLogic::setGemType(int x, int y, GemType type)
{
  m_logicBoard[x][y] = type;
}

void BoardLogic::newBoard(int x, int y, MoveInfo &moveInfo)
{
  std::vector<std::vector<GemType>> newLogicBoard(x, std::vector<GemType>(y));
  m_logicBoard = newLogicBoard;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      GemType type = GemType(rand() % GT_COUNT);
      moveInfo.addCreation(Creation(i, j, type));
      m_logicBoard[i][j] = type;
    }
  }
}

void BoardLogic::swapGems(Coordinates src, Coordinates dst, MoveInfo& moveInfo)
{
  std::cout << "Src: " << coordsToString(src) << std::endl;
//  moveInfo.addInvalidSwap(InvalidSwap(src, dst));
//  moveInfo.addCreation(src);
  findConnections(m_logicBoard, moveInfo);
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
  int minLength = 3;

  // search in cols
  int sameGems = 1;

  for (int i = 0; i < logicBoard.size(); i++) {
    sameGems = 1;
    for (int j = 0; j < logicBoard[i].size() - 1; j++) {
      if (logicBoard[i][j] == logicBoard[i][j+1]) {
        sameGems++;
        if (j+1 == logicBoard[i].size() - 1) { // if next gem is is the last gem
          if (sameGems >= minLength) {
            for (int y = j + 1; y > j + 1 - sameGems; y--) {
              moveInfo.addAnnihilation(Coordinates(i,y));
            }
          }
          sameGems = 1;
        }
      } else {
        if (sameGems >= minLength) {
          for (int y = j; y > j - sameGems; y--) {
            moveInfo.addAnnihilation(Coordinates(i,y));
          }
        }
        sameGems = 1;
      } // else (next gem is different)
    } // for col
  } // for row

  // search in rows
  sameGems = 1;

  for (int j = 0; j < logicBoard.size(); j++) {
    sameGems = 1;
    for (int i = 0; i < logicBoard[j].size() - 1; i++) {
      if (logicBoard[i][j] == logicBoard[i+1][j]) {
        sameGems++;
        if (i+1 == logicBoard.size() - 1) {
          if (sameGems >= minLength) {
            for (int x = i + 1; x > i + 1 - sameGems; x--) {
              moveInfo.addAnnihilation(Coordinates(x,j));
            }
          }
        }
      } else {
        if (sameGems >= minLength) {
          for (int x = i; x > i - sameGems; x--) {
            moveInfo.addAnnihilation(Coordinates(x,j));
          }
        }
        sameGems = 1;
      } // else (next gem is different)
    } // for col
  } // for row
}

void BoardLogic::updateBoard(MoveInfo& moveInfo)
{
}
