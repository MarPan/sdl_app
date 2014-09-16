#include <sstream>
#include "gameoverstate.h"
#include "playtimestate.h"
#include "texturemanager.h"

GameOverState::GameOverState(int points)
  : m_fontName("Compass.ttf")
  , m_textLine1("GAME OVER")
  , m_textLine2("Click to play again")
{
  m_textColor.r = 255;
  m_textColor.g = 255;
  m_textColor.b = 255;
  std::stringstream ss;
  ss << points;
  m_sPoints = "Points: " + ss.str();
  theTextureManager.loadText(m_fontName, m_sPoints, m_textColor, 36);
  theTextureManager.loadText(m_fontName, m_textLine1, m_textColor, 86);
  theTextureManager.loadText(m_fontName, m_textLine2, m_textColor, 46);
  m_sizeText1 = theTextureManager.getSize(m_textLine1);
  m_sizeText2 = theTextureManager.getSize(m_textLine2);
  m_pointsTexSize = theTextureManager.getSize(m_sPoints);
}

void GameOverState::update(float dt)
{

}

void GameOverState::draw()
{
  theTextureManager.draw(m_textLine1, 200, 100, m_sizeText1.first, m_sizeText1.second);
  theTextureManager.draw(m_textLine2, 200, 200, m_sizeText2.first, m_sizeText2.second);
  theTextureManager.draw(m_sPoints, 220, 300, m_pointsTexSize.first, m_pointsTexSize.second);
}

GameState* GameOverState::input(SDL_Event &event)
{
  switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
      return new PlayTimeState();
      break;
    default:
      break;
  }
  return nullptr;
}
