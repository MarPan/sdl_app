#include <iostream>
#include <sstream>
#include <iomanip>
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
  int timeStr = event.user.code;
  m_pBoard->setTime(getStringTime(timeStr));
}

void PlayTimeState::draw()
{
  m_pBoard->draw();
}

void PlayTimeState::onClick(int x, int y)
{
  m_pBoard->onClick(x, y);
}

std::string PlayTimeState::getStringTime(int time)
{
    std::stringstream timeText;
    timeText.str( "" );
    timeText << std::setw(2) << std::setfill('0') << time/60 << ":" << std::setw(2) << std::setfill('0') << time%60;
    return timeText.str();
}
