#include <ctime>
#include <iostream>
#include "board.h"
#include "gemcontroller.h"
#include "texturemanager.h"
#include "boardlogic.h"

Board::Board(int rows, int cols)
  : Object()
  , m_size(Coordinates(rows,cols))
  , m_backgroundPath("BackGround.jpg")
  , m_gemWidth(42)
  , m_gems(rows, std::vector<GemController*>(cols))
  , m_gemsOffset(Coordinates(345,125))
{
  setState(new BoardStates::IdleState(this));
  m_boardLogic = new BoardLogic(rows, cols);

  std::srand(std::time(0));

  for (int i = 0; i < GT_COUNT; i++) {
    std::string path;
    switch (i) {
      case GT_BLUE:
        path = "Blue.png";
        break;
      case GT_GREEN:
        path = "Green.png";
        break;
      case GT_PURPLE:
        path = "Purple.png";
        break;
      case GT_RED:
        path = "Red.png";
        break;
      case GT_YELLOW:
        path = "Yellow.png";
        break;
    }
    m_gemRegistry.insert(std::make_pair(GemType(i), path));
    theTextureManager.load(path, path);
  }

  theTextureManager.load(m_backgroundPath, m_backgroundPath);
  for (int i = 0; i < m_size.first; i++) {
    for (int j = 0; j < m_size.second; j++) {
      m_gems[i][j] = new GemController(i,j, this);
      m_gems[i][j]->setType(GemType(rand() % GT_COUNT));
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
      m_gems[i][j]->setType(GemType(rand() % GT_COUNT));
}

bool Board::swapGems(Coordinates gemOne, Coordinates gemTwo)
{
  std::cout << "swapping " << gemOne.first << " " << gemOne.second
            << " with " << gemTwo.first << " " << gemTwo.second << std::endl;
  std::swap(m_gems[gemOne.first][gemOne.second], m_gems[gemTwo.first][gemTwo.second]);

  m_gemsInMotion.push_back(m_gems[gemOne.first][gemOne.second]);
  m_gemsInMotion.push_back(m_gems[gemTwo.first][gemTwo.second]);
  m_gems[gemOne.first][gemOne.second]->moveTo(gemOne);
  m_gems[gemTwo.first][gemTwo.second]->moveTo(gemTwo);
  // it might be beneficial, to store all moving gems
  // I will call BoardLogic::tick() only when the last gem stopped moving

  return true;
}

void Board::gemFinishedMoving(GemController *gem)
{
  for (int i = 0; i < m_gemsInMotion.size(); i++) {
    if (gem == m_gemsInMotion[i]) {
      m_gemsInMotion.erase(m_gemsInMotion.begin() + i);
      break;
    }
  }
  MoveInfo moveInfo;
  if (m_gemsInMotion.empty())
    m_boardLogic->updateBoard(moveInfo);

  parseMoveInfo(moveInfo);
}

void Board::parseMoveInfo(const MoveInfo& moveInfo)
{
  for (auto& is : moveInfo.getInvalidSwaps()) {
    // set multiple destinations
    // for both gems
  }
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

bool Board::clickGem(int x, int y)
{
  return m_gems[x][y]->onClicked();
}

void Board::onClick(int x, int y)
{
  BoardStates::BoardState* state = getState()->onClick(x,y);
  if (state != nullptr) {
    setState(state);
  }
}

Coordinates Board::getGemsOffset()
{
  return m_gemsOffset;
}

int Board::getTileWidth()
{
  return m_gemWidth;
}

Coordinates Board::getSize()
{
  return m_size;
}

std::string Board::getGemPath(GemType gt)
{
  return m_gemRegistry[gt];
}

void Board::setSelectedGem(Coordinates coords)
{
  m_selectedGem = coords;
}


Coordinates Board::getSelectedGem() const
{
  return m_selectedGem;
}
