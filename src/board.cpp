#include "board.h"
#include "gem.h"


Board::Board(int rows, int cols)
  : size(std::pair<int,int>(rows,cols))
{
  for (int i = 0; i < size.first; i++)
  {
    gems.push_back(std::vector<Gem*>());
    for (int j = 0; j < size.second; j++)
      gems[i].push_back(new Gem());
  }
}

Board::~Board()
{
  for (int i = 0; i < size.first; i++)
    for (int j = 0; j < size.second; j++)
      delete gems[i][j];
}
