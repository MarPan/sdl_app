#ifndef OBJECT_H
#define OBJECT_H

#include <utility>
class SDL_Renderer;

class Object
{
public:
  Object();

  void update(float dt);
  void draw();

private:
  std::pair<int, int> _position;
  std::pair<float, float> _speed;  // speed per second
};

#endif // OBJECT_H
