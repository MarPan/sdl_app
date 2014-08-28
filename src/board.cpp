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
  , m_Time("00:00")
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

  for (int i = 0; i < m_size.first; i++) {
    for (int j = 0; j < m_size.second; j++) {
        m_gems[i][j] = nullptr;
      }
    }

  theTextureManager.load(m_backgroundPath, m_backgroundPath);
  MoveInfo moveInfo;
  m_boardLogic->newBoard(m_size.first, m_size.second, moveInfo);
  parseMoveInfo(moveInfo);
}

Board::~Board()
{
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)
      delete m_gems[i][j];
}

bool Board::swapGems(Coordinates gemOne, Coordinates gemTwo)
{
  // it might be beneficial, to store all moving gems
  // I will call BoardLogic::tick() only when the last gem stopped moving
  m_gemsInMotion.push_back(m_gems[gemOne.first][gemOne.second]);
  m_gemsInMotion.push_back(m_gems[gemTwo.first][gemTwo.second]);

  MoveInfo moveInfo;
  m_boardLogic->swapGems(gemOne, gemTwo, moveInfo);
  parseMoveInfo(moveInfo);

  return true;
}

void Board::gemFinishedMoving(GemController *gem)
{
  for (size_t i = 0; i < m_gemsInMotion.size(); i++) {
    if (gem == m_gemsInMotion[i]) {
      m_gemsInMotion.erase(m_gemsInMotion.begin() + i);
      break;
    }
  }

  if (m_gemsInMotion.empty()) {
    std::cout << "All gems finished moving" << std::endl;
    MoveInfo moveInfo;
    m_boardLogic->updateBoard(moveInfo);
    parseMoveInfo(moveInfo);
  }
}

void Board::parseMoveInfo(const MoveInfo& moveInfo)
{
  for (auto& is : moveInfo.getInvalidSwaps()) {
    // set multiple destinations
    // for both gems
    // and this is why I should make my own Coordinates class instead of std::pair
    m_gems[is.first.first][is.first.second]->addMoveTo(is.second);
    m_gems[is.first.first][is.first.second]->addMoveTo(is.first);

    m_gems[is.second.first][is.second.second]->addMoveTo(is.first);
    m_gems[is.second.first][is.second.second]->addMoveTo(is.second);
  }

  for (auto& r : moveInfo.getRelocations()) {
    m_gems[r.first.first][r.first.second]->addMoveTo(r.second);
  }

  for (auto& a : moveInfo.getAnnihilations()) {
    // how do I deal with gem removal? Do I simply delete them?
    // or do I create "invisible" gem?
    m_gems[a.first][a.second]->remove();
  }

  for (auto& c : moveInfo.getCreations()) {
    if (m_gems[c.first][c.second]) {
      if (m_gems[c.first][c.second]->isRemoved() == false) {
        std::cout << "WARNING: creating new gem on top of a previous one\n";
      }
      delete m_gems[c.first][c.second];
    }
    m_gems[c.first][c.second] =
          new GemController(c.first, -1, this); // create it over the board
    m_gems[c.first][c.second]->setType(c.type);
    m_gems[c.first][c.second]->addMoveTo(Coordinates(c.first, c.second)); // let it fall to its place
  }
}

void Board::update(float dt)
{
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)
      if (m_gems[i][j])
        m_gems[i][j]->update(dt);

  SDL_Color textColor = { 0, 0, 255 };
  //std::cout << "action_man" + m_Time;
  theTextureManager.loadTextWithFont("Action-Man/Action_Man.ttf", "action_man" + m_Time, m_Time, textColor, 56);
}

void Board::draw()
{
  theTextureManager.draw(m_backgroundPath, 0, 0, 755, 600);
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)      
      if (m_gems[i][j])
        m_gems[i][j]->draw();
  //draw clock
  theTextureManager.draw("action_man" + m_Time, 90, 200, theTextureManager.getSize("action_man" + m_Time).first, theTextureManager.getSize("action_man" + m_Time).second);
}

bool Board::clickGem(int x, int y)
{
  if (m_gems[x][y])
    return m_gems[x][y]->onClicked();
  return false;
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

void Board::setTime(std::string time)
{
  m_Time = time;
}

Coordinates Board::getSelectedGem() const
{
  return m_selectedGem;
}
