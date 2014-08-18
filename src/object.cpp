#include <SDL2/SDL_render.h>
#include "object.h"
#include "game.h"

Object::Object()
{

}


void Object::update(float dt)
{
  m_position.first += m_speed.first * dt / 1000;
  m_position.second += m_speed.second * dt / 1000;
}
void Object::draw()
{

}
