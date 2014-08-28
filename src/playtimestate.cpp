#include <iostream>
#include "playtimestate.h"

PlayTimeState::PlayTimeState()
{
  m_pBoard = new Board(8, 8);
}

void PlayTimeState::update(float dt)
{
  m_pBoard->update(dt);
}

void PlayTimeState::input(SDL_Event &event)
{
  std::string timeStr = static_cast<char*>(event.user.data1);
  std::cout << "SDL_UserEvent arrived with time " << timeStr << std::endl;
  m_pBoard->setTime(timeStr);
}

void PlayTimeState::draw()
{
  m_pBoard->draw();
}

void PlayTimeState::onClick(int x, int y)
{
  m_pBoard->onClick(x, y);
}
