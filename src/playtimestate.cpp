#include "playtimestate.h"

PlayTimeState::PlayTimeState()
{
  m_pBoard = new Board(8, 8);
}

void PlayTimeState::update(float dt)
{
  m_pBoard->update(dt);
}

void PlayTimeState::draw()
{
  m_pBoard->draw();
}

void PlayTimeState::onClick(int x, int y)
{
  m_pBoard->onClick(x, y);
  // TODO:
  // propagate a click to a board
  // then a board shall (depending on its state)
  //  * select a gem
  //  * swap new gem with previously selected
  //  * (and so on)
}
