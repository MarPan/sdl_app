#ifndef OBJECT_H
#define OBJECT_H

#include <utility>
#include <string>
#include "multiplatformSDL.h"

class Object
{
public:
  Object();

  virtual ~Object() { }
  virtual void update(float dt);
  virtual void draw();
  void print(std::string str);

  std::pair<int,int> getPosition();
  std::pair<int,int> getSize();  
  std::string getTexId();
  void setSize(std::pair<int,int> size);
  void setOffset(int offX, int offY);
  void setTexId(std::string texId);
  void setPosition(std::pair<int,int> position);

  // temporary - i will make it nice later
  std::pair<int,int> m_movementDestination;

protected:
  std::pair<int,int> m_position;
  std::pair<float, float> m_speed;  // speed in pixels per second
  std::pair<int, int> m_size;
  std::pair<int, int> m_offset;
  std::string m_texId;

};

#endif // OBJECT_H
