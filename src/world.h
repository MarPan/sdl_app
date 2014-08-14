#ifndef WORLD_H
#define WORLD_H

#include <vector>
class Object;
class SDL_Renderer;

class World
{
public:
  World();

  void update(float dt);
  void draw(SDL_Renderer *renderer);

private:
  std::vector<Object*> _objects;
};

#endif // WORLD_H
