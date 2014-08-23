#include "board.h"
#include <ctime>
#include "gem.h"
#include "gemtyperegistry.h"


Board::Board(int rows, int cols)
  : Object(0.0f,0.0f)
  , m_size(std::pair<int,int>(rows,cols))
  , m_backgroundPath("BackGround.jpg")
  , m_gemWidth(42)
  , m_gemsOffset(std::pair<int,int>(345,125))
{
  setState(new IdleState(this));
  std::srand(std::time(0));

  for (int i = 0; i < Gem::GT_COUNT; i++) {
    std::string path;
    switch (i) {
      case Gem::GT_BLUE:
        path = "Blue.png";
        break;
      case Gem::GT_GREEN:
        path = "Green.png";
        break;
      case Gem::GT_PURPLE:
        path = "Purple.png";
        break;
      case Gem::GT_RED:
        path = "Red.png";
        break;
      case Gem::GT_YELLOW:
        path = "Yellow.png";
        break;
    }
    m_gemRegistry.insert(std::make_pair(Gem::GemType(i), path));
    theTextureManager.load(path, path);
  }

  theTextureManager.load(m_backgroundPath, m_backgroundPath);
  for (int i = 0; i < m_size.first; i++)
  {
    m_gems.push_back(std::vector<Gem*>());
    for (int j = 0; j < m_size.second; j++)
      {
      m_gems[i].push_back(new Gem(i,j, Gem::GemType(rand() % Gem::GT_COUNT), this));
      }
  }
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

void Board::selectGem(int x, int y)
{
  m_gems[x][y]->select();
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

std::pair<int,int> Board::getGemsOffset()
{
  return m_gemsOffset;
}

int Board::getTileWidth()
{
  return m_gemWidth;
}

std::pair<int,int> Board::getSize()
{
  return m_size;
}

std::string Board::getGemPath(Gem::GemType gt)
{
  return m_gemRegistry[gt];
}