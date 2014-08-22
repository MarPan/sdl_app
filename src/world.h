#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
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
  std::vector<Object*> m_objects;
  std::string m_backgroundPath;
  std::pair<int, int> boardOrigin;
};

#endif // WORLD_H
