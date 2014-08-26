#include <iostream>
#include <cmath>
#include "multiplatformSDL.h"
#include "texturemanager.h"
#include "object.h"
#include "game.h"

Object::Object()
  : m_speed(1,1)
  , m_destinationReached(true)
{ }

void Object::print(std::string str = "")
{
  std::cout << str << " " << m_position.first << " " << m_position.second <<
               " " << m_size.first << " " << m_size.second << std::endl;
}

void Object::update(float dt)
{
  if (m_destination == m_position) {
    if (m_destinationReached == false) {
      notify(ObjectEvent::DESTINATION_REACHED);
    }
    m_destinationReached = true;
    return;
  }

  m_destinationReached ? m_destinationReached = false : m_destinationReached;

  int hDir = 0, vDir = 0;
  if (m_destination.first - m_position.first > 0) {
    hDir = 1;
  } else if (m_destination.first - m_position.first < 0) {
    hDir = -1;
  }

  if (m_destination.second - m_position.second > 0) {
    vDir = 1;
  } else if (m_destination.second - m_position.second < 0) {
    vDir = -1;
  }

  m_position.first += std::ceil(m_speed.first * dt) * hDir;
  m_position.second += std::ceil(m_speed.second * dt) * vDir;
}

void Object::draw()
{
//  print(m_texId);
  theTextureManager.draw(m_texId,
                         m_position.first,
                         m_position.second,
                         getSize().first,
                         getSize().second
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

void Object::setPosition(Coordinates position)
{
  m_position = position;
  m_destination = position;
}

void Object::setDestination(Coordinates destination)
{
  m_destination = destination;
}

