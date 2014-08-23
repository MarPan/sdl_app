#include "boardstate.h"
#include "board.h"
#include <iostream>

BoardState::BoardState()
{
}

BoardState::~BoardState()
{
}

IdleState::IdleState(Board *board)
  : m_pBoard(board)
{

}

void IdleState::onClick(int x, int y)
{
  // TODO:
  // find out which gem is at x, y
  // and inform it that it's clicked

  x -= m_pBoard->getGemsOffset().first;
  y -= m_pBoard->getGemsOffset().second;

  std::cout << "CLICK " << x << " " << y << std::endl;

  if (x > 0 && y > 0 &&
      x < m_pBoard->getSize().first * m_pBoard->getGemWidth() &&
      y < m_pBoard->getSize().second * m_pBoard->getGemWidth()) {
    x /= m_pBoard->getGemWidth();
    y /= m_pBoard->getGemWidth();
    m_pBoard->selectGem(x, y);
  }
}

void IdleState::update(float dt)
{

}

void IdleState::draw()
{

}
