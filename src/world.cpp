#include "world.h"
#include "object.h"

#include <SDL2/SDL_render.h>

World::World()
{
}

void World::update(float dt)
{
  for (std::size_t i = 0; i < _objects.size(); i++)
    _objects.at(i)->update(dt);
}

void World::draw(SDL_Renderer *renderer)
{
  for (std::size_t i = 0; i < _objects.size(); i++)
    _objects.at(i)->draw(renderer);
}
