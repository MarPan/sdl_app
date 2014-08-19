#ifndef OBJECT_H
#define OBJECT_H

#include <utility>
#include <string>
#include <SDL2/SDL.h>

class Object
{
public:
  Object();
  Object(float posX, float posY);
  Object(std::pair<float,float> position);

  virtual ~Object() { }
  virtual void update(float dt);
  virtual void draw();
  void print(std::string str);

protected:
  std::pair<float, float> m_position;
  std::pair<float, float> m_speed;  // speed in pixels per second
  std::pair<int, int> m_size;
};

#endif // OBJECT_H
