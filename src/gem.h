#ifndef GEM_H
#define GEM_H

#include "object.h"
#include "state.h"
#include "texturemanager.h"

/*
 *
 *  http://www.reddit.com/r/gamedev/comments/2a9gsq/match3_games_logic_use_a_2d_array_or_store/
 *
Give each tile a state, RESTING, FALLING, etc, then on your update, run through the tile array and test that they're all in a final position (ie RESTING), then recalculate.
Very efficient, and allows you to have fancy exploding bombs and stuff that all run at different speeds.
You can safely update your table at the start of the animation, as the tiles will be in a "FALLING" state, and the table grid can't update if any tile is not resting
 */

class Gem;

class GemState : public State
{
public:
  GemState() {};
  void onEnter(Gem &gem);
  virtual void update(float dt) {};
  virtual void draw() {
    theTextureManager.draw(m_texId, m_positionAndSize);
  };
private:
  std::string m_texId;
  SDL_Rect m_positionAndSize;
};

class GemIdleState : public GemState
{
public:
  GemIdleState() {}
};

class GemFallingState : public GemState
{
public:
  GemFallingState() {}
};

class Gem : public Object
{
  friend class GemState;

public:
  Gem(float posX, float posY);
  Gem(std::pair<float, float> position);
  void update(float dt);
  void draw();

  void changeState(GemState *state);

  std::string texId;
private:
  void init();
  GemState *m_state;
};

#endif // GEM_H
