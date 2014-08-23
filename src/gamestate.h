#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:
  GameState();

  virtual void onClick(int x, int y);
  virtual void update(int dt);
  virtual void draw();
};

#endif // GAMESTATE_H
