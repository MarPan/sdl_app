#include "boardstate.h"
#include "board.h"
#include <iostream>

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
  m_pBoard->swapGems(m_pBoard->getSelectedGem(), coords);
  return new IdleState(m_pBoard);
}
