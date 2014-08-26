#include <iostream>
#include <cmath>
#include "multiplatformSDL.h"
#include "texturemanager.h"
#include "object.h"
#include "game.h"

Object::Object()
  : m_speed(1,1)
  , m_angle(0)
  , m_rotationSpeed(0)
  , m_rotationToDo(0)
  , m_rotationDirection(1)
{ }

Object::~Object()
{
}

void Object::print(std::string str = "")
{
  std::cout << str << " " << m_position.first << " " << m_position.second <<
               " " << m_size.first << " " << m_size.second << std::endl;
}

void Object::update(float dt)
{
  move(dt);
  rotate(dt);
}

void Object::rotate(float dt)
{
  if (m_rotationSpeed == 0 || m_rotationToDo == 0) {
    return;
  }

  double rotationInThisFrame = m_rotationSpeed * dt;
  if (rotationInThisFrame > m_rotationToDo) {
    m_angle += m_rotationToDo * m_rotationDirection;
    m_rotationToDo = 0;
    notify(ObjectEvent::ROTATION_FINISHED);
  } else {
    m_rotationToDo -= rotationInThisFrame;
    m_angle += rotationInThisFrame * m_rotationDirection;
  }
}

void Object::move(float dt)
{
  if (m_destinations.empty()) {
    return;
  }

  Coordinates& destination = m_destinations.front();

  if (destination == m_position) {
    m_destinations.pop_front();
    if (m_destinations.empty()) {
      notify(ObjectEvent::DESTINATION_REACHED);
    }
    return;
  }

  int hDir = 0, vDir = 0;
  if (destination.first - m_position.first > 0) {
    hDir = 1;
  } else if (destination.first - m_position.first < 0) {
    hDir = -1;
  }

  if (destination.second - m_position.second > 0) {
    vDir = 1;
  } else if (destination.second - m_position.second < 0) {
    vDir = -1;
  }

  // not ideal, since I will have a set minimal speed 1 pixel per frame
  // maybe I should store an offset as a float
  m_position.first += std::ceil(m_speed.first * dt) * hDir;
  m_position.second += std::ceil(m_speed.second * dt) * vDir;
}

void Object::draw()
{
  theTextureManager.draw(m_texId,
                         m_position.first,
                         m_position.second,
                         getSize().first,
                         getSize().second,
                         m_angle
                         );
}

void Object::setSize(Coordinates size)
{
  m_size = size;
}

void Object::setTexId(std::string texId)
{
  m_texId = texId;
  setSize(theTextureManager.getSize(texId));
}

Coordinates Object::getPosition()
{
  return m_position;
}

Coordinates Object::getSize()
{
  return m_size;
}

std::string Object::getTexId()
{
  return m_texId;
}

void Object::setRotation(double angle, double speed)
{
  m_rotationSpeed = speed;
  m_rotationToDo = angle;
}

void Object::setPosition(Coordinates position)
{
  std::cout << "setPosition " << m_texId << std::endl;
  m_position = position;
  m_destinations.clear();
}

void Object::setDestination(Coordinates destination)
{
  std::cout << "setDestination";
  m_destinations.clear();
  addDestination(destination);
}

void Object::addDestination(Coordinates destination)
{
  m_destinations.push_back(destination);
}
