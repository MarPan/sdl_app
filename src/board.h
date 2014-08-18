#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "object.h"

class Gem;

class Board : public Object
{
public:
  Board(int rows, int cols);
  ~Board();

  void update(float dt);
  void draw();

  std::pair<int, int> size;
  std::vector<std::vector<Gem*>> gems;
};

#endif // BOARD_H
