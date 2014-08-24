#ifndef BOARD_LOGIC_HPP
#define BOARD_LOGIC_HPP

#include <vector>
#include <cstddef>
#include "gem.h"
#include "moveinfo.h"

class BoardLogic
{

public:
  std::shared_ptr<MoveInfo> resetBoard(int rows, int cols);
  std::shared_ptr<MoveInfo> makeMove(int srcRow, int srcCol, int dstX, int dstY);
  std::shared_ptr<MoveInfo> makeMove(const std::pair<int,int>& src, const std::pair<int,int>& dst);
  std::shared_ptr<MoveInfo> updateBoard();
  std::shared_ptr<MoveInfo> dumpBoardState() const;

  bool isMoveValid(int srcRow, int srcCol, int dstRow, int dstCol);
  bool isMoveValid(const std::pair<int,int>& src, const std::pair<int,int>& dst);
  bool hasConnections() const;

protected:
  void createBoard(int rows, int cols);
  void fillBoard();
  bool hasConnections(const std::vector<std::vector<Gem::GemType>>& board) const;
  Gem::GemType setNewGem(const std::pair<int,int>& coords);
  std::shared_ptr<MoveInfo> getBoardChanges();

private:
  std::vector<std::vector<Gem::GemType>> m_board;
  size_t m_cols;
  size_t m_rows;

  enum { MIN_CONNECTION_SIZE = 3 };
};

#endif // BOARD_LOGIC_HPP
