#include "board.h"
#include "gem.h"


Board::Board(int rows, int cols)
  : size(std::pair<int,int>(rows,cols)),
    Object(0.0f,0.0f)
{
  for (int i = 0; i < size.first; i++)
  {
    gems.push_back(std::vector<Gem*>());
    for (int j = 0; j < size.second; j++)
      {
      gems[i].push_back(new Gem(std::pair<float,float>(i,j)));
      gems[i][j]->print("");
      }
  }
}

Board::~Board()
{
  for (int i = 0; i < gems.size(); i++)
    for (int j = 0; j < gems[i].size(); j++)
      delete gems[i][j];
}

void Board::update(float dt)
{
  for (int i = 0; i < gems.size(); i++)
    for (int j = 0; j < gems[i].size(); j++)
      gems[i][j]->update(dt);
}

void Board::draw()
{
  for (int i = 0; i < gems.size(); i++)
    for (int j = 0; j < gems[i].size(); j++)
      gems[i][j]->draw();
}