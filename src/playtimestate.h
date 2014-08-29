#ifndef PLAYTIMESTATE_H
#define PLAYTIMESTATE_H

#include "board.h"
#include "gamestate.h"
#include "clock.h"

class PlayTimeState : public GameState
{
public:
  PlayTimeState();
  ~PlayTimeState();
  void update(float dt);
  void draw();
  GameState* input(SDL_Event &event);

private:  
  void onClick(int x, int y);

  Board* m_pBoard;
  std::string m_backgroundPath;
  int const m_gameTime;
  SDL_Color m_textColor;

  int m_Points;
  std::string m_sPoints;
  std::pair<int,int> m_pointsTexSize;
  int m_timeLeft;
  std::string m_sTime;
  std::pair<int,int> m_timeTextSize;

  std::string m_fontName;
  std::pair<int,int> m_bgSize;

  Clock *m_pClock;
};

#endif // PLAYTIMESTATE_H
