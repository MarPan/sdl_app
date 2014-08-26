#ifndef OBJECT_H
#define OBJECT_H

#include <deque>
#include "utilities.h"
#include "notifier.h"
#include "multiplatformSDL.h"

enum class ObjectEvent { DESTINATION_REACHED };

class Object : public Notifier<ObjectEvent>
{
public:
  Object();

  virtual ~Object() { }
  virtual void update(float dt);
  virtual void draw();
  void print(std::string str);

  Coordinates getPosition();
  Coordinates getSize();  
  std::string getTexId();
  void setSize(Coordinates size);
  void setTexId(std::string texId);
  void setPosition(Coordinates position);
  void setDestination(Coordinates position); //< clears destinations and sets a new one
  void addDestination(Coordinates position);

protected:
  Coordinates m_position;
  std::pair<float, float> m_speed;  //< speed in pixels per second
  Coordinates m_size;
  std::deque<Coordinates> m_destinations;  //< object will be moved towards this point
  std::string m_texId;
};

#endif // OBJECT_H
