#include "boardlogic.h"
#include <ctime>

MoveInfo* BoardLogic::resetBoard(int rows, int cols)
{
  createBoard(rows, cols);

  do {
    fillBoard();
  } while (hasConnections());

  return dumpBoardState();
}

void BoardLogic::createBoard(int rows, int cols)
{
  m_cols = static_cast< size_t >(cols);
  m_rows = static_cast< size_t >(rows);

  m_board = std::vector<std::vector<Gem::GemType>>(m_rows, std::vector<Gem::GemType>(m_cols));
}

MoveInfo* BoardLogic::makeMove(int srcRow, int srcCol, int dstRow, int dstCol)
{
  MoveInfo* moveInfo = new MoveInfo();

  if (isMoveValid(srcRow, srcCol, dstRow, dstCol))  {
    std::swap(m_board[srcRow][srcCol], m_board[dstRow][dstCol]);
    moveInfo->addSwap(MoveInfo::Swap(std::pair<int,int>(srcRow, srcCol), std::pair<int,int>(dstRow, dstCol)));
  } else {
    moveInfo->addInvalidSwap(MoveInfo::InvalidSwap(std::pair<int,int>(srcRow, srcCol), std::pair<int,int>(dstRow, dstCol)));
  }

  return moveInfo;
}

MoveInfo* BoardLogic::makeMove(const std::pair<int,int>& from, const std::pair<int,int>& to)
{
  return makeMove(from.first, from.second, to.first, to.second);
}

MoveInfo* BoardLogic::updateBoard()
{
  return getBoardChanges();
}

MoveInfo* BoardLogic::dumpBoardState() const
{
  MoveInfo* moveInfo = new MoveInfo();
  for (size_t i = 0; i < m_rows; ++i) {
    for (size_t j = 0; j < m_cols; ++j) {
      moveInfo->addNewGem(MoveInfo::NewGem(m_board[i][j], std::pair<int,int>(i, j)));
    }
  }

  return moveInfo;
}

bool BoardLogic::isMoveValid(int srcRow, int srcCol, int dstRow, int dstCol)
{
  bool retVal = false;
  std::swap(m_board[srcRow][srcCol], m_board[dstRow][dstCol]);
  retVal = hasConnections(m_board);
  std::swap(m_board[srcRow][srcCol], m_board[dstRow][dstCol]);
  return retVal;
}

bool BoardLogic::isMoveValid(const std::pair<int,int>& from, const std::pair<int,int>& to)
{
  return isMoveValid(from.first, from.second, to.first, to.second);
}

bool BoardLogic::hasConnections() const
{
  return hasConnections(m_board);
}

bool BoardLogic::hasConnections(const std::vector<std::vector<Gem::GemType>>& board) const
{
  // search for connections in rows
  for (size_t i = 0; i < m_rows; ++i) {
    int subsequent = 1;
    for (size_t j = 1; j < m_cols; ++j) {
      if (board[i][j - 1] == board[i][j]) {
        subsequent += 1;
        if (subsequent >= MIN_CONNECTION_SIZE) {
          return true;
        }
      } else {
        subsequent = 1;
      }
    }
  }

  // search for connections in cols
  for (size_t j = 0; j < m_cols; ++j) {
    int subsequent = 1;
    for (size_t i = 1; i < m_rows; ++i) {
      if (board[i - 1][j] == board[i][j]) {
        subsequent += 1;
        if (subsequent >= MIN_CONNECTION_SIZE) {
          return true;
        }
      } else {
        subsequent = 1;
      }
    }
  }

  return false;
}

void BoardLogic::fillBoard()
{
  for (size_t i = 0; i < m_rows; ++i) {
    for (size_t j = 0; j < m_cols; ++j)  {
      setNewGem(std::pair<int,int>(i, j));
    }
  }
}

MoveInfo* BoardLogic::getBoardChanges()
{
  MoveInfo* moveInfo = new MoveInfo();

  for (size_t i = 0; i < m_rows; ++i) {
    for (size_t j = 1; j < m_cols; ++j) {
      if (m_board[i][j - 1] == m_board[i][j]) {
        int subsequent = 2;
        for (size_t k = j + 1; k < m_cols && m_board[i][k] == m_board[i][k - 1]; ++k) {
          ++subsequent;
        }

        if (subsequent >= MIN_CONNECTION_SIZE) {
          MoveInfo::Connection connection;
          for (size_t k = j - 1; k < j - 1 + subsequent; ++k) {
            connection.addGem(std::pair<int,int>(i, k), m_board[i][k]);
          }
          moveInfo->addConnection(connection);
        }

        j += subsequent - 2;
      }
    }
  }

  for (size_t j = 0; j < m_cols; ++j) {
    for (size_t i = 1; i < m_rows; ++i) {
      if (m_board[i - 1][j] == m_board[i][j]) {
        int subsequent = 2;
        for (size_t k = i + 1; k < m_rows && m_board[k][j] == m_board[k - 1][j]; ++k) {
          ++subsequent;
        }

        if (subsequent >= MIN_CONNECTION_SIZE) {
          MoveInfo::Connection connection;
          for (size_t k = i - 1; k < i - 1 + subsequent; ++k) {
            connection.addGem(std::pair<int,int>(k, j), m_board[k][j]);
          }
          moveInfo->addConnection(connection);
        }

        i += subsequent - 2;
      }
    }
  }

  std::vector<std::vector<bool>> filled(m_rows, std::vector<bool>(m_cols, true));

  for each (auto connection in moveInfo->getConnections()) {
    size_t length = connection.getSize();
    for (size_t i = 0; i < length; ++i) {
      auto coords = connection[i].coords;
      filled[coords.first][coords.second] = false;
    }
  }

  for (size_t j = 0; j < m_cols; ++j) {
    for (size_t i = m_rows - 1; i >= 0; --i) {
      if (!filled[i][j]) {
        int zeros = 0;
        while (i >= 0 && !filled[i][j]) {
          ++zeros;
          --i;
        }
        for (size_t k = i + zeros; k > i; --k) {
          if (k - zeros >= 0) {
            std::swap(filled[k][j], filled[k - zeros][j]);
            std::swap(m_board[k][j], m_board[k - zeros][j]);
            moveInfo->addRelocation(MoveInfo::Relocation(std::pair<int,int>(k - zeros, j), std::pair<int,int>(k, j)));
          } else {
            filled[k][j] = true;
            Gem::GemType newGemType = setNewGem(std::pair<int,int>(k, j));
            moveInfo->addNewGem(MoveInfo::NewGem(newGemType, std::pair<int,int>(k, j)));
          }
        }
        i += 2;
      }
    }
  }

  return moveInfo;
}

Gem::GemType BoardLogic::setNewGem(const std::pair<int,int>& coords)
{
  Gem::GemType newGemType = Gem::GemType(rand() % Gem::GT_COUNT);
  m_board[coords.first][coords.second] = newGemType;
  return newGemType;
}

