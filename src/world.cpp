#include "world.h"
#include "board.h"

World::World()
{

}

World::~World()
{
  for (size_t i = 0; i < m_objects.size(); i++)
    delete m_objects[i];
}

void World::add(Object *object)
{
  m_objects.push_back(object);
}

void World::update(float dt)
{
  for (std::size_t i = 0; i < m_objects.size(); i++)
    m_objects.at(i)->update(dt);
}

void World::draw()
{
  for (std::size_t i = 0; i < m_objects.size(); i++)
    m_objects.at(i)->draw();
}
