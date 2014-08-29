#ifndef PLAYTIMESTATE_H
#define PLAYTIMESTATE_H

#include "board.h"
#include "gamestate.h"

//class Board;

class PlayTimeState : public GameState
{
public:
  PlayTimeState();
  void onClick(int x, int y);
  void update(float dt);
  void draw();

  int pts;
private:
  Board* m_pBoard;
  std::string m_backgroundPath;
  std::string m_sPoints;
  std::pair<int,int> m_pointsTexSize;
  std::string m_fontName;
  std::pair<int,int> m_bgSize;
  SDL_Color m_textColor;
};

#endif // PLAYTIMESTATE_H
