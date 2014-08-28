#include "boardlogic.h"

BoardLogic::BoardLogic(int x, int y)
  : m_logicBoard(x, std::vector<GemType>(y))
  , m_points(0)
{
}

void BoardLogic::newBoard(int x, int y, MoveInfo &moveInfo)
{
  m_points = 0;
  std::vector<std::vector<GemType>> newLogicBoard(x, std::vector<GemType>(y));
  m_logicBoard = newLogicBoard;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      GemType type = GemType(rand() % GT_COUNT);
      //moveInfo.addCreation(Creation(i, j, type));
      m_logicBoard[i][j] = type;
    }
  }

  std::vector<Coordinates> gemsToBeRemoved;
  do {
    MoveInfo annihilations;
    gemsToBeRemoved.clear();
    findConnections(m_logicBoard, annihilations);
    for (Coordinates coords : annihilations.getAnnihilations()) {
      gemsToBeRemoved.push_back(coords);
    }
    removeGems(gemsToBeRemoved, annihilations);
    std::cout << gemsToBeRemoved.size() << std::endl;
  }
  while (gemsToBeRemoved.empty() == false);

  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      moveInfo.addCreation(Creation(i, j, m_logicBoard[i][j]));
    }
  }
  resetPoints();
}
// moveInfo will be filled with annihilations of gems
// that are in connections
void BoardLogic::findConnections(MoveInfo &moveInfo)
{
  findConnections(m_logicBoard, moveInfo);
}

void BoardLogic::swapGems(Coordinates src, Coordinates dst, MoveInfo& moveInfo)
{

//  void print() {
    std::cout<<"LOGIC: ";
    for (int j = 0; j < 8; j++)
      {
        std::cout<<"\n";
        for (int i = 0; i < 8; i++)
          {
            std::cout<<m_logicBoard[i][j]<<" "; }
      }
//  }

  if (isMovePossible(src, dst)) {
    moveInfo.addSwap(Swap(src, dst));
    std::swap(m_logicBoard[src.first][src.second], m_logicBoard[dst.first][dst.second]);
  } else {
    moveInfo.addInvalidSwap(InvalidSwap(src, dst));
  }
}

bool BoardLogic::isMovePossible(Coordinates src, Coordinates dst)
{
  auto copy = m_logicBoard;
  std::swap(copy[src.first][src.second], copy[dst.first][dst.second]);
  MoveInfo moveInfo;
  return findConnections(copy, moveInfo);
}

void BoardLogic::removeGems(const std::vector<Coordinates>& toBeRemoved, MoveInfo& moveInfo)
{
  std::vector<int> emptyGemsCount(m_logicBoard.size());
  for (int i = 0; i < emptyGemsCount.size(); i++) {
    emptyGemsCount[i] = false;
  }

  // set the gems to -1 or sth
  for (int i = 0; i < toBeRemoved.size(); i++) {
    m_logicBoard[toBeRemoved[i].first][toBeRemoved[i].second] = GT_INVALID;
    emptyGemsCount[toBeRemoved[i].first]++;
  }

  // easier: for each column, starting from the bottomn, I count invalid gems
  // when I find real gem, I move it down by invalidGemsCount
  // GENIALNE

  std::vector<std::vector<GemType>> copy = m_logicBoard;
  for (int i = 0; i < m_logicBoard.size(); i++) {
    if (emptyGemsCount[i] == 0) {
      continue;
    }
    int emptyCount = 0;
    for (int j = m_logicBoard[i].size() - 1; j >= 0 ; j--) {
      if (m_logicBoard[i][j] == GT_INVALID) {
        emptyCount++;
      } else if (emptyCount != 0) {
        moveInfo.addRelocation(Relocation(Coordinates(i,j), Coordinates(i,j+emptyCount)));
        std::swap(copy[i][j], copy[i][j+emptyCount]);
      }
    }
  }

  // create new gems for the ones removed
  for (int i = 0; i < m_logicBoard.size(); i++) {
    for (int j = 0; j < m_logicBoard[i].size(); j++) {
      if (copy[i][j] == GT_INVALID) {
        GemType type = GemType(rand() % GT_COUNT);
        moveInfo.addCreation(Creation(i, j, type));
        copy[i][j] = type;
      }
    }
  }

  m_logicBoard = copy;
}



void BoardLogic::handleConnectionInRow(int row, int startCol, int length, MoveInfo &moveInfo)
{
  if (length == 3) {
    for (int x = startCol; x > startCol - length; x--) {
      moveInfo.addAnnihilation(Coordinates(x,row));
    }
    m_points += 3;
  } else { // matched more than 3 - remove whole row!
    for (int x = 0; x < m_logicBoard.size(); x++) {
      moveInfo.addAnnihilation(Coordinates(x,row));
    }
    m_points += m_logicBoard.size();
  }
}

void BoardLogic::handleConnectionInColumn(int column, int startRow, int length, MoveInfo &moveInfo)
{
  if (length == 3) {
    for (int y = startRow; y > startRow - length; y--) {
      moveInfo.addAnnihilation(Coordinates(column, y));
    }
    m_points += 3;
  } else { // matched more than 3 - remove whole column!
    for (int y = 0; y < m_logicBoard[column].size(); y++) {
      moveInfo.addAnnihilation(Coordinates(column,y));
    }
    m_points += m_logicBoard.size();
  }
}


// scans the board. If finds connection, adds Annihilation to the moveInfo
bool BoardLogic::findConnections(const std::vector<std::vector<GemType>>& logicBoard, MoveInfo& moveInfo)
{
  // I don't have an easy way to spot combined connections, like
  // *
  // * * *
  // *
  // all I can do is to analyze coords of created annihilations later on

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
            handleConnectionInColumn(i, j + 1, sameGems, moveInfo);
          }
          sameGems = 1;
        }
      } else {
        if (sameGems >= minLength) {
          handleConnectionInColumn(i, j, sameGems, moveInfo);
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
            handleConnectionInRow(j, i + 1, sameGems, moveInfo);
          }
        }
      } else {
        if (sameGems >= minLength) {
          handleConnectionInRow(j, i, sameGems, moveInfo);
        }
        sameGems = 1;
      } // else (next gem is different)
    } // for col
  } // for row
  if (moveInfo.getAnnihilations().size()) {
    return true;
  }
  return false;
}

void BoardLogic::updateBoard(MoveInfo& moveInfo)
{
 // std::cout << "BoardLogic tick!" << std::endl;
}

int BoardLogic::getPoints()
{
  return m_points;
}

void BoardLogic::resetPoints()
{
  m_points = 0;
}
