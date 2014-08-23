#ifndef OBJECT_H
#define OBJECT_H

#include <utility>
#include <string>
#include "multiplatformSDL.h"

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

  std::pair<float,float> getPosition();
  std::pair<float,float> getSize();  
  std::string getTexId();
  void setSize(int width);
  void setOffset(int offX, int offY);

protected:
  std::pair<float, float> m_position;
  std::pair<float, float> m_speed;  // speed in pixels per second
  std::pair<int, int> m_size;
  std::pair<int, int> m_offset;
  std::string m_texId;
};

#endif // OBJECT_H
