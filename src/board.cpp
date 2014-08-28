#include <ctime>
#include <iostream>
#include "board.h"
#include "gemcontroller.h"
#include "texturemanager.h"
#include "boardlogic.h"
#include "soundmanager.h"

Board::Board(int rows, int cols)
  : Object()
  , m_size(Coordinates(rows,cols))
  , m_backgroundPath("BackGround.jpg")
  , m_gemWidth(42)
  , m_gems(rows, std::vector<GemController*>(cols))
  , m_gemsOffset(Coordinates(345,125))
  , m_selectedGem(nullptr)
{
  setState(new BoardStates::IdleState(this));
  m_boardLogic = new BoardLogic(rows, cols);

  std::srand(std::time(0));
  std::srand(200);

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
  theSoundManager.load("sounds/Pop.ogg", "sounds/Pop.ogg", SoundType::MUSIC);
  theSoundManager.load("sounds/click1.wav", "sounds/click1.wav", SoundType::SFX);

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
  MoveInfo moveInfo;
  m_boardLogic->swapGems(gemOne, gemTwo, moveInfo);
  parseMoveInfo(moveInfo);
  return true; // TODO
}

void Board::gemFinishedMoving(GemController *gem)
{
  if (gem == m_selectedGem) {
  // if (gem->isSelected()) {
    gem->onClicked();
    m_selectedGem = nullptr; // maybe I shoud store a ptr
  }

  if (gem->isRemoved()) {
    m_gemsToBeRemoved.push_back(gem->getCoordinates());
  } else {
    theSoundManager.playSound("sounds/click1.wav", 0);
  }

  for (size_t i = 0; i < m_gemsInMotion.size(); i++) {
    if (gem == m_gemsInMotion[i]) {
      m_gemsInMotion.erase(m_gemsInMotion.begin() + i);
      break;
    }
  }

  if (m_gemsInMotion.empty()) {
    std::cout << "All gems finished moving" << std::endl;
    setState(new BoardStates::IdleState(this));
    MoveInfo moveInfo;
    if (m_gemsToBeRemoved.size()) {
      m_boardLogic->removeGems(m_gemsToBeRemoved, moveInfo);
      m_gemsToBeRemoved.clear();
    } else {
      m_boardLogic->findConnections(moveInfo);
    }
    parseMoveInfo(moveInfo);
  }
}

void Board::parseMoveInfo(const MoveInfo& moveInfo)
{
  // std::cout<<"\n\n\n\n";
  for (auto& is : moveInfo.getInvalidSwaps()) {
    theSoundManager.playMusic("sounds/Pop.ogg", 0);
    // set multiple destinations for both gems
    // and this is why I should make my own Coordinates class instead of std::pair
    m_gems[is.first.first][is.first.second]->addMoveTo(is.second);
    m_gems[is.first.first][is.first.second]->addMoveTo(is.first);

    m_gems[is.second.first][is.second.second]->addMoveTo(is.first);
    m_gems[is.second.first][is.second.second]->addMoveTo(is.second);

    m_gemsInMotion.push_back(m_gems[is.first.first][is.first.second]);
    m_gemsInMotion.push_back(m_gems[is.second.first][is.second.second]);
  }

  for (auto& r : moveInfo.getRelocations()) {
    m_gems[r.first.first][r.first.second]->addMoveTo(r.second);
    m_gemsInMotion.push_back(m_gems[r.first.first][r.first.second]);
    std::swap(m_gems[r.first.first][r.first.second], m_gems[r.second.first][r.second.second]);
  }

  for (auto& r : moveInfo.getSwaps()) {
    m_gems[r.first.first][r.first.second]->addMoveTo(r.second);
    m_gems[r.second.first][r.second.second]->addMoveTo(r.first);
    m_gemsInMotion.push_back(m_gems[r.first.first][r.first.second]);
    m_gemsInMotion.push_back(m_gems[r.second.first][r.second.second]);
    std::swap(m_gems[r.first.first][r.first.second], m_gems[r.second.first][r.second.second]);
  }

  for (auto& a : moveInfo.getAnnihilations()) {
    // only mark gem - it won't be rendered.
    // we will delete it when a new gem will be creatad on top of it.
    if (m_gems[a.first][a.second]->remove()) {
      m_gemsInMotion.push_back(m_gems[a.first][a.second]);
    }
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
    m_gemsInMotion.push_back(m_gems[c.first][c.second]);
  }
  if (m_gemsInMotion.size()) {
    std::cout << "setting GEMSMOVINGSTATE " << std::endl;
    setState(new BoardStates::GemsMovingState(this));
  }
}

void Board::update(float dt)
{
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)
      if (m_gems[i][j])
        m_gems[i][j]->update(dt);
}

void Board::draw()
{
  theTextureManager.draw(m_backgroundPath, 0, 0, 755, 600);
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)      
      if (m_gems[i][j])
        m_gems[i][j]->draw();
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
  m_selectedGem = m_gems[coords.first][coords.second];
}

Coordinates Board::getSelectedGem() const
{
  return m_selectedGem->getCoordinates();
}

int Board::getPoints()
{
  return m_boardLogic->getPoints();
}
