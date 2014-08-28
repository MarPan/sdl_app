#include <iostream>
#include "playtimestate.h"

PlayTimeState::PlayTimeState()
{
  m_pBoard = new Board(8, 8);
}

void PlayTimeState::update(float dt)
{
  if (pts != m_pBoard->getPoints()) {
    std::cout << "POINTS: " << m_pBoard->getPoints() << std::endl;
    pts = m_pBoard->getPoints();
  }
  m_pBoard->update(dt);

}

void PlayTimeState::draw()
{
  m_pBoard->draw();
}

void PlayTimeState::onClick(int x, int y)
{
  m_pBoard->onClick(x, y);
}
