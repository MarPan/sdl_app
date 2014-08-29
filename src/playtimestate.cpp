#include <sstream>
#include <iostream>
#include "playtimestate.h"
#include "texturemanager.h"

PlayTimeState::PlayTimeState()
  : m_backgroundPath("BackGround.jpg")
  , m_fontName("Jersey M54.ttf")
{
  m_textColor.r = 0;
  m_textColor.g = 0;
  m_textColor.b = 0;
  m_textColor.a = 255;
  m_pBoard = new Board(8, 8);  
  theTextureManager.load(m_backgroundPath, m_backgroundPath);
  m_bgSize = theTextureManager.getSize(m_backgroundPath);
}

void PlayTimeState::update(float dt)
{
  if (pts != m_pBoard->getPoints()) {
    std::stringstream ss;
    ss << m_pBoard->getPoints();
    if (ss.str() != m_sPoints) {
      m_sPoints = ss.str();
      theTextureManager.loadText(m_fontName, m_sPoints, m_textColor, 46);
      m_pointsTexSize = theTextureManager.getSize(m_sPoints);
    }
  }
  m_pBoard->update(dt);

}

void PlayTimeState::draw()
{
  theTextureManager.draw(m_backgroundPath, 0, 0,
                         m_bgSize.first, m_bgSize.second);
  m_pBoard->draw();
  theTextureManager.draw(m_sPoints, 96, 435,
                         m_pointsTexSize.first, m_pointsTexSize.second);
}

void PlayTimeState::onClick(int x, int y)
{
  m_pBoard->onClick(x, y);
}
