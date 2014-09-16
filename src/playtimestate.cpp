#include <sstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "playtimestate.h"
#include "gameoverstate.h"
#include "texturemanager.h"

PlayTimeState::PlayTimeState()
  : m_backgroundPath("BackGround.jpg")
  , m_gameTime(60)
  , m_sTime("Time: 01:00")
  , m_Points(-1)
  , m_fontName("Compass.ttf")
{
  m_textColor.r = 20;
  m_textColor.g = 20;
  m_textColor.b = 20;
  m_pBoard = new Board(8, 8);  

  theTextureManager.load(m_backgroundPath, m_backgroundPath);
  m_bgSize = theTextureManager.getSize(m_backgroundPath);

  theTextureManager.loadText(m_fontName, m_sTime, m_textColor, 36);
  m_timeTextSize = theTextureManager.getSize(m_sTime);

  m_pClock = new Clock();
  m_pClock->start(1); // send event once per second
}

void PlayTimeState::update(float dt)
{
  if (m_Points != m_pBoard->getPoints()) {
    std::stringstream ss;
    m_Points = m_pBoard->getPoints();
    ss << m_Points;
    if (ss.str() != m_sPoints) {
      m_sPoints = ss.str();
      theTextureManager.loadText(m_fontName, m_sPoints, m_textColor, 36);
      m_pointsTexSize = theTextureManager.getSize(m_sPoints);
    }
  }
  m_pBoard->update(dt);

}

GameState *PlayTimeState::input(SDL_Event &event)
{
  switch (event.type)  {
    case SDL_MOUSEBUTTONDOWN:
      m_pBoard->onClick(event.button.x, event.button.y);
      break;
    case SDL_USEREVENT:
      std::stringstream ss;
      m_timeLeft = m_gameTime - event.user.code;
      ss << std::setw(2) << std::setfill('0') << m_timeLeft/60 << ":" << std::setw(2) << std::setfill('0') << m_timeLeft % 60;
      m_sTime = "Time: " + ss.str();
      theTextureManager.loadText(m_fontName, m_sTime, m_textColor, 36);
      m_timeTextSize = theTextureManager.getSize(m_sTime);
      if (m_timeLeft == -1) {
        return new GameOverState(m_Points);
      }
      break;
  }
  return nullptr;
}

void PlayTimeState::draw()
{
  theTextureManager.draw(m_backgroundPath, 0, 0,
                         m_bgSize.first, m_bgSize.second);
  m_pBoard->draw();
  theTextureManager.draw(m_sPoints, 96, 435,
                         m_pointsTexSize.first, m_pointsTexSize.second);

  //draw clock
  theTextureManager.draw(m_sTime, 36, 190, m_timeTextSize.first, m_timeTextSize.second);
}

PlayTimeState::~PlayTimeState()
{
  m_pClock->stop();
  delete m_pClock;
}
