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

void BoardState::onEnter()
{
  std::cout << "StateChagned\n";
}

void BoardState::onExit()
{ }

BoardState::~BoardState()
{ }

BoardState* BoardState::onClick(int x, int y)
{
  std::cout << x << " " << y << std::endl;
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
  std::cout << "BOARD IdleState" << std::endl;
}

BoardState* IdleState::onClick(int x, int y)
{
  auto coords = translateToTileCoords(x,y);
  if (coords.first >= 0 && coords.second >= 0) {
    if (m_pBoard->clickGem(coords.first, coords.second))
      return new SelectedState(m_pBoard, coords);
  }
  return nullptr;
}

SelectedState::SelectedState(Board* board, Coordinates selectedGem)
  : BoardState(board)
  , m_selectedGem(selectedGem)
{ std::cout << "BOARD SelectedState " << coordsToString(m_selectedGem) << std::endl; }

BoardState* SelectedState::onClick(int x, int y)
{
  auto coords = translateToTileCoords(x,y);
  
  //std::cout << "Dest: " << coords.first << " " << coords.second << std::endl;
  if ((abs(m_selectedGem.first - coords.first) == 1 && m_selectedGem.second == coords.second) ||
      (abs(m_selectedGem.second - coords.second) == 1 && m_selectedGem.first == coords.first)) {
    m_pBoard->swapGems(m_selectedGem, coords);
    m_pBoard->deselectGem(coords);
    return new GemsMovingState(m_pBoard);
  } else {
    return new IdleState(m_pBoard);
  }
}

void SelectedState::onExit()
{
  std::cout << "-------\n Leaving SelectedState " << coordsToString(m_selectedGem) << std::endl;
  m_pBoard->deselectGem(m_selectedGem);
}

GemsMovingState::GemsMovingState(Board *board)
  : BoardState(board)
{ std::cout << "BOARD GemsMovingState" << std::endl; }


}
