#include "board.h"
#include <ctime>
#include "gem.h"


Board::Board(int rows, int cols)
  : Object(0.0f,0.0f),
    size(std::pair<int,int>(rows,cols)),
    m_backgroundPath("../resources/BackGround.jpg"),
    m_tileWidth(64)
{
  setState(new IdleState(this));

  theTextureManager.load(m_backgroundPath, m_backgroundPath);
  for (int i = 0; i < size.first; i++)
  {
    m_gems.push_back(std::vector<Gem*>());
    for (int j = 0; j < size.second; j++)
      {
      m_gems[i].push_back(new Gem(i,j, m_tileWidth, Gem::GemType(rand() % Gem::GT_COUNT)));
      }
  }

  std::srand(std::time(0));
}

Board::~Board()
{
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)
      delete m_gems[i][j];
}

void Board::fillBoard()
{
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)
      m_gems[i][j]->setType(Gem::GemType(rand() % Gem::GT_COUNT));
}

bool Board::swapGems(std::pair<int,int> gemOne, std::pair<int,int> gemTwo)
{
  Gem *tmp = m_gems[gemOne.first][gemOne.second];
  m_gems[gemOne.first][gemOne.second] = m_gems[gemTwo.first][gemTwo.second];
  m_gems[gemTwo.first][gemTwo.second] = tmp;
  //TO DO: are you sure it should return bool?
  //Currently I added return true for compilation purpose.
  return true;
}

void Board::update(float dt)
{
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)
      m_gems[i][j]->update(dt);
}

void Board::draw()
{
  theTextureManager.draw(m_backgroundPath, 0, 0, 755, 600);
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)
      m_gems[i][j]->draw();
}

void Board::onClick(int x, int y)
{
  getState()->onClick(x,y);
}
