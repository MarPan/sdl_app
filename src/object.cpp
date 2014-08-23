#include <SDL_render.h>
#include <iostream>
#include "texturemanager.h"t"
#include "object.h"
#include "game.h"

Object::Object()
  : m_size(std::pair<int,int>(0,0))
{ }
Object::Object(std::pair<float, float> position)
  : m_position(position)
  , m_size(std::pair<int,int>(0,0))
{ }
Object::Object(float posX, float posY)
  : m_position(std::pair<float,float>(posX,posY))
  , m_size(std::pair<int,int>(0,0))
{ }

void Object::print(std::string str = "")
{
  std::cout << str << " " << m_position.first << " " << m_position.second <<
               " " << m_size.first << " " << m_size.second << std::endl;
}

void Object::update(float dt)
{
  m_position.first += m_speed.first * dt / 1000;
  m_position.second += m_speed.second * dt / 1000;
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

void Object::setSize(int width)
{
  m_size = std::pair<float,float>(width, width);
}

void Object::setOffset(int offX, int offY)
{
  m_offset = std::pair<int, int>(offX, offY);
}

std::pair<float,float> Object::getPosition()
{
  return m_position;
}

std::pair<float,float> Object::getSize()
{
  return m_size;
}

std::string Object::getTexId()
{
  return m_texId;
}

