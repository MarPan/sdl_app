#include <SDL_render.h>
#include <iostream>
#include <cmath>
#include "texturemanager.h"
#include "object.h"
#include "game.h"

Object::Object()
  : m_size(std::pair<int,int>(0,0))
  , m_movementDestination(-1,-1)
  , m_speed(1,1)
{ }

void Object::print(std::string str = "")
{
  std::cout << str << " " << m_position.first << " " << m_position.second <<
               " " << m_size.first << " " << m_size.second << std::endl;
}

void Object::update(float dt)
{
  if (m_movementDestination.first == m_position.first && 
      m_movementDestination.second == m_position.second) {
    //std::cout << "END THIS MADNESS" << std::endl;
    return;
  }
  
  int xRoad = m_movementDestination.first - m_position.first;
  int yRoad = m_movementDestination.second - m_position.second;

  if (xRoad < 0)
    xRoad = -1;
  else 
    xRoad = 1;

  if (yRoad < 0)
    yRoad = -1;
  else 
    yRoad = 1;

  std::cout << m_movementDestination.first << " " << m_position.first << " " << std::endl;

  if (m_movementDestination.first != m_position.first) {
    m_position.first += std::ceil(m_speed.first * dt * xRoad);
  }
  if (m_movementDestination.second != m_position.second) {
    m_position.second += std::ceil(m_speed.second * dt * yRoad);
  }
}

void Object::draw()
{
  theTextureManager.draw(m_texId,
                         m_position.first + m_offset.first,
                         m_position.second + m_offset.second,
                         getSize().first,
                         getSize().second
                        );
}

void Object::setSize(std::pair<int,int> size)
{
  m_size = size;
}

void Object::setOffset(int offX, int offY)
{
  m_offset = std::pair<int, int>(offX, offY);
}

void Object::setTexId(std::string texId)
{
  m_texId = texId;
}

std::pair<int,int> Object::getPosition()
{
  return m_position;
}

std::pair<int,int> Object::getSize()
{
  return m_size;
}

std::string Object::getTexId()
{
  return m_texId;
}

void Object::setPosition(std::pair<int,int> position)
{
  m_position = position;
  m_movementDestination = position;
}