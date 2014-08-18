#ifndef GEM_H
#define GEM_H

#include "object.h"

class Gem : public Object
{
public:
  Gem();
  void update(float dt);
  void draw();
};

#endif // GEM_H
