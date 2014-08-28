#ifndef BOARDLOGIC_H
#define BOARDLOGIC_H

#include <vector>
#include "gemcontroller.h"
#include "moveinfo.h"

class BoardLogic
{
public:
  BoardLogic(int x, int y);

  // these will fill the MoveInfo
  void newBoard(int x, int y, MoveInfo &moveInfo);
  void swapGems(Coordinates src, Coordinates dst, MoveInfo& moveInfo);
  void updateBoard(MoveInfo& moveInfo);

  void findConnections(MoveInfo &moveInfo);
  // removing gems will result in other falling down.
  void removeGems(const std::vector<Coordinates> &toBeRemoved, MoveInfo& moveInfo);

  int getPoints();
  void resetPoints();

private:
  bool isMovePossible(Coordinates src, Coordinates dst);
  bool findConnections(const std::vector<std::vector<GemType>>& logicBoard, MoveInfo& moveInfo);
  void handleConnectionInRow(int row, int startCol, int length, MoveInfo &moveInfo);
  void handleConnectionInColumn(int column, int startRow, int length, MoveInfo &moveInfo);

  std::vector<std::vector<GemType>> m_logicBoard;
  int m_points;
};

#endif // BOARDLOGIC_H
