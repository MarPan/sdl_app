#include <SDL2/SDL_render.h>
#include "object.h"
#include "game.h"

Object::Object()
{

}


void Object::update(float dt)
{
  _position.first += _speed.first * dt;
  _position.second +=_speed.second * dt;
}
void Object::draw()
{

}
