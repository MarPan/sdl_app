#include "world.h"
#include "board.h"

#include <SDL2/SDL_render.h>

World::World()
{
}

World::~World()
{
  for (size_t i = 0; i < _objects.size(); i++)
    delete _objects[i];
}

void World::add(Object *object)
{
  _objects.push_back(object);
}

void World::update(float dt)
{
  for (std::size_t i = 0; i < _objects.size(); i++)
    _objects.at(i)->update(dt);
}

void World::draw()
{
  for (std::size_t i = 0; i < _objects.size(); i++)
    _objects.at(i)->draw();
}
