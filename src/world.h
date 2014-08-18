#ifndef WORLD_H
#define WORLD_H

#include <vector>
class Object;
class SDL_Renderer;

class World
{
public:
  World();
  ~World();

  void update(float dt);
  void draw();
  void add(Object *object);

private:
  std::vector<Object*> _objects;
};

#endif // WORLD_H
