#include <ctime>
#include <iostream>
#include <algorithm>
#include "board.h"
#include "gemcontroller.h"
#include "texturemanager.h"
#include "boardlogic.h"
#include "soundmanager.h"

Board::Board(int rows, int cols)
  : Object()
  , m_size(Coordinates(rows,cols))
  , m_gemWidth(42)
  , m_gems(rows, std::vector<GemController*>(cols))
  , m_gemsOffset(Coordinates(345,125))
  , m_Time("00:00")
  , m_gemsRemovedSfx("match1.ogg")
  , m_gemFellSfx("fall.ogg")
  , m_invalidMoveSfx("break.ogg")
{
  setState(new BoardStates::IdleState(this));
  m_boardLogic = new BoardLogic(rows, cols);

  std::srand(std::time(0));
  //std::srand(200);

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

  MoveInfo moveInfo;
  m_boardLogic->newBoard(m_size.first, m_size.second, moveInfo);
  parseMoveInfo(moveInfo);

  theSoundManager.load(m_gemsRemovedSfx, m_gemsRemovedSfx, SoundType::SFX);
  theSoundManager.load(m_invalidMoveSfx, m_invalidMoveSfx, SoundType::SFX);
  theSoundManager.load(m_gemFellSfx, m_gemFellSfx, SoundType::SFX);
}

void Board::setState(const state_type& state)
{
  if (m_state) {
    m_state->onExit();
    delete m_state;
  }
  m_state = state;
  m_state->onEnter();
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
  if (gem->isRemoved()) {
    m_gemsToBeRemoved.push_back(gem->getCoordinates());
  } else {
    theSoundManager.playSound(m_gemFellSfx, 0);
  }

  for (size_t i = 0; i < m_gemsInMotion.size(); i++) {
    if (gem == m_gemsInMotion[i]) {
      m_gemsInMotion.erase(m_gemsInMotion.begin() + i);
      break;
    }
  }

  if (m_gemsInMotion.empty()) {
    // std::cout << "All gems finished moving" << std::endl;
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
  // INVALID SWAPS
  for (auto& is : moveInfo.getInvalidSwaps()) {
    theSoundManager.playSound(m_invalidMoveSfx, 0);
    // set multiple destinations for both gems
    // and this is why I should make my own Coordinates class instead of std::pair
    m_gems[is.first.first][is.first.second]->addMoveTo(is.second);
    m_gems[is.first.first][is.first.second]->addMoveTo(is.first);

    m_gems[is.second.first][is.second.second]->addMoveTo(is.first);
    m_gems[is.second.first][is.second.second]->addMoveTo(is.second);

    m_gemsInMotion.push_back(m_gems[is.first.first][is.first.second]);
    m_gemsInMotion.push_back(m_gems[is.second.first][is.second.second]);
  }


  // RELOCATIONS
  for (auto& r : moveInfo.getRelocations()) {
    m_gems[r.first.first][r.first.second]->addMoveTo(r.second);
    m_gemsInMotion.push_back(m_gems[r.first.first][r.first.second]);
    std::swap(m_gems[r.first.first][r.first.second], m_gems[r.second.first][r.second.second]);
  }


  // SWAPS
  for (auto& r : moveInfo.getSwaps()) {
    m_gems[r.first.first][r.first.second]->addMoveTo(r.second);
    m_gems[r.second.first][r.second.second]->addMoveTo(r.first);
    m_gemsInMotion.push_back(m_gems[r.first.first][r.first.second]);
    m_gemsInMotion.push_back(m_gems[r.second.first][r.second.second]);
    std::swap(m_gems[r.first.first][r.first.second], m_gems[r.second.first][r.second.second]);
  }


  // ANNIHILATIONS
  for (auto& a : moveInfo.getAnnihilations()) {
    // only mark gem - it won't be rendered.
    // we will delete it when a new gem will be creatad on top of it.
    theSoundManager.playSound(m_gemsRemovedSfx, 0);
    if (m_gems[a.first][a.second]->remove()) {
      m_gemsInMotion.push_back(m_gems[a.first][a.second]);
    }
  }


  // CREATIONS
  std::vector<std::vector<Creation>> newGemsInColumn(m_gems.size());
  for (auto& c : moveInfo.getCreations()) {
    if (m_gems[c.first][c.second]) {
      if (m_gems[c.first][c.second]->isRemoved() == false) {
        std::cout << "WARNING: creating new gem on top of a previous one\n";
      }
      delete m_gems[c.first][c.second];
    }
    newGemsInColumn[c.first].push_back(c);
  }

  for (int i = 0 ; i < newGemsInColumn.size(); i++) {
    std::sort(newGemsInColumn[i].begin(), newGemsInColumn[i].end());
    for (int j = 0; j < newGemsInColumn[i].size(); j++) {
      Creation &c = newGemsInColumn[i][j];
      m_gems[c.first][c.second] = new GemController(c.first, c.second - newGemsInColumn[i].size(), this);
      m_gems[c.first][c.second]->setType(c.type);
      m_gems[c.first][c.second]->addMoveTo(Coordinates(c.first, c.second)); // let it fall to its place
      m_gemsInMotion.push_back(m_gems[c.first][c.second]);
    }
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

// @args Logical coords
void Board::deselectGem(Coordinates gem)
{
  if (m_gems[gem.first][gem.second]->isSelected()) {
    m_gems[gem.first][gem.second]->onClicked();
  }
}

std::string Board::getGemPath(GemType gt)
{
  return m_gemRegistry[gt];
}

int Board::getPoints() const
{
  return m_boardLogic->getPoints();
}
