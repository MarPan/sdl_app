#include <SDL_render.h>
#include <iostream>
#include "texturemanager.h"
#include "object.h"
#include "game.h"

Object::Object()
  : m_size(std::pair<int,int>(0,0))
{ }
Object::Object(std::pair<int, int> position)
  : m_position(position)
  , m_size(std::pair<int,int>(0,0))
{ }
Object::Object(int posX, int posY)
  : m_position(std::pair<int,int>(posX,posY))
  , m_size(std::pair<int,int>(0,0))
{ }

void Object::print(std::string str = "")
{
  std::cout << str << " " << m_position.first << " " << m_position.second <<
               " " << m_size.first << " " << m_size.second << std::endl;
}

void Object::update(float dt)
{
  m_position.first += int(m_speed.first * dt);
  m_position.second += int(m_speed.second * dt);
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
}