#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "gamestate.h"

class GameOverState : public GameState
{
public:
  GameOverState(int points);
  void update(float dt);
  void draw();
  GameState* input(SDL_Event &event);

private:
  std::string m_textLine1, m_textLine2;
  std::pair<int,int> m_sizeText1, m_sizeText2;
  std::string m_fontName;
  SDL_Color m_textColor;

  std::string m_sPoints;
  std::pair<int,int> m_pointsTexSize;
};

#endif // GAMEOVERSTATE_H
