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

  void setRotation(double angle, double speed);

protected:
  Coordinates m_position;
  std::pair<float, float> m_speed;  //< speed in pixels per second
  std::deque<Coordinates> m_destinations;  //< object will be moved towards this point

  Coordinates m_size;
  std::string m_texId;

  double m_angle;
  double m_rotationSpeed;  // in degrees per second, so 360 means one turnaround per second
  double m_rotationToDo;
  short int m_rotationDirection; // -1 or 1

  void move(float dt);
  void rotate(float dt);
};

#endif // OBJECT_H
