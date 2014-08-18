#ifndef OBJECT_H
#define OBJECT_H

#include <utility>
class SDL_Renderer;

class Object
{
public:
  Object();

  virtual void update(float dt);
  virtual void draw();

protected:
  std::pair<int, int> m_position;
  std::pair<float, float> m_speed;  // speed in pixels per second
};

#endif // OBJECT_H
