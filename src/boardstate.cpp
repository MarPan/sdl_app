#include "boardstate.h"
#include "board.h"
#include <iostream>


namespace BoardStates {

BoardState::BoardState(Board *board)
  : m_pBoard(board)
{
}

std::pair<int,int> BoardState::translateToTileCoords(int x, int y)
{
  auto retVal = std::make_pair(-1, -1);
  x -= m_pBoard->getGemsOffset().first - m_pBoard->getTileWidth() / 2;
  y -= m_pBoard->getGemsOffset().second - m_pBoard->getTileWidth() / 2;

  if (x > 0 && y > 0 &&
      x < m_pBoard->getSize().first * m_pBoard->getTileWidth() &&
      y < m_pBoard->getSize().second * m_pBoard->getTileWidth()) {

    x /= m_pBoard->getTileWidth();
    y /= m_pBoard->getTileWidth();
    retVal = std::make_pair(y,x);
  }
  return retVal;
}


BoardState::~BoardState()
{
}

BoardState* BoardState::onClick(int x, int y)
{
  if (m_pBoard->getLogic()->hasConnections()) {
    std::cout << "BattleGameState::MoveDoneSlot board has connections" << std::endl;
    auto moveInfo = m_pBoard->getLogic()->updateBoard();
    m_pBoard->updateBoard(moveInfo);
  } else {
    std::cout << "BattleGameState::MoveDoneSlot no connections" << std::endl;
  }
  return nullptr;
}

void BoardState::update(float dt)
{

}

void BoardState::draw()
{

}

IdleState::IdleState(Board *board)
  : BoardState(board)
{
}

BoardState* IdleState::onClick(int x, int y)
{
  auto coords = translateToTileCoords(x,y);
  if (coords.first != -1) {
    if (m_pBoard->getGem(coords.first, coords.second)->onClicked())
      m_pBoard->setSelectedGem(coords);
      return new SelectedState(m_pBoard);
  }
  return nullptr;
}

SelectedState::SelectedState(Board* board)
  : BoardState(board)
{ }

BoardState* SelectedState::onClick(int x, int y)
{
  auto coords = translateToTileCoords(x,y);
  auto prevCoords = m_pBoard->getSelectedGem();
  
  if ((abs(prevCoords.first - coords.first) == 1 && prevCoords.second == coords.second) ||
      (abs(prevCoords.second - coords.second) == 1 && prevCoords.first == coords.first)) {
    std::shared_ptr<MoveInfo> moveInfo = m_pBoard->getLogic()->makeMove(prevCoords, coords);
    m_pBoard->updateBoard(moveInfo);
    BoardState::onClick(x,y);
  } else if (prevCoords.first == coords.first && prevCoords.second == coords.second) {
    m_pBoard->getGem(coords.first, coords.second)->onClicked();
  } else {
    m_pBoard->getGem(prevCoords.first, prevCoords.second)->onClicked();
  }
  return new IdleState(m_pBoard);
}

} // namespace BoardStates