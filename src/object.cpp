#include <SDL2/SDL_render.h>
#include <iostream>
#include "object.h"
#include "game.h"

Object::Object(std::pair<float, float> position)
  : m_position(position)
{ }
Object::Object(float posX, float posY)
  : m_position(std::pair<float,float>(posX,posY))
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

}
