#include "boardstate.h"
#include "board.h"
#include <iostream>


namespace BoardStates {

BoardState::BoardState(Board *board)
  : m_pBoard(board)
{
}

Coordinates BoardState::translateToTileCoords(int x, int y)
{
  auto retVal = std::make_pair(-1, -1);
  x -= m_pBoard->getGemsOffset().first - m_pBoard->getTileWidth() / 2;
  y -= m_pBoard->getGemsOffset().second - m_pBoard->getTileWidth() / 2;

  if (x > 0 && y > 0 &&
      x < m_pBoard->getSize().first * m_pBoard->getTileWidth() &&
      y < m_pBoard->getSize().second * m_pBoard->getTileWidth()) {

    x /= m_pBoard->getTileWidth();
    y /= m_pBoard->getTileWidth();
    retVal = std::make_pair(x,y);
  }
  return retVal;
}


BoardState::~BoardState()
{
}

BoardState* BoardState::onClick(int x, int y)
{
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
    if (m_pBoard->clickGem(coords.first, coords.second))
      m_pBoard->setSelectedGem(coords);
      //std::cout << "Selected: " << coords.first << " " << coords.second << std::endl;
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
  
  //std::cout << "Dest: " << coords.first << " " << coords.second << std::endl;
  if ((abs(prevCoords.first - coords.first) == 1 && prevCoords.second == coords.second) ||
      (abs(prevCoords.second - coords.second) == 1 && prevCoords.first == coords.first)) {
    m_pBoard->swapGems(m_pBoard->getSelectedGem(), coords);
  } else {
    m_pBoard->clickGem(prevCoords.first, prevCoords.second);
  }
  return new IdleState(m_pBoard);
}

}
