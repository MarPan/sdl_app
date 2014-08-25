#include <iostream>
#include "gemcontroller.h"
#include "board.h"

GemController::GemController(int x, int y, Board* board)
  : m_gem(new Object())
  , m_pBoard(board)
{
  setCoords(std::make_pair(x, y));
  setState(new GemStates::GemIdleState(m_gem));;
}

void GemController::setCoords(std::pair<int,int> coords)
{
  m_logicalCoords = coords;
  m_gem->setPosition(computePosition(coords));
}

void GemController::setType(GemType type)
{
  m_type = type;
  m_gem->setTexId(m_pBoard->getGemPath(m_type));
  m_gem->setPosition(computePosition(m_logicalCoords));  // because size might have changed
}


std::pair<int,int> GemController::computePosition(std::pair<int,int> coords)
{
  std::pair<int,int> tileMiddle(getBoard()->getGemsOffset().first +
                                coords.first * getBoard()->getTileWidth(),
                                getBoard()->getGemsOffset().second +
                                coords.second * getBoard()->getTileWidth());

  tileMiddle.first -= m_gem->getSize().first / 2;
  tileMiddle.second -= m_gem->getSize().second / 2;

  return tileMiddle;
  //m_gem->setPosition(tileMiddle);

    std::cout << "From " << coords.first << "," << coords.second <<
                 "to   " << tileMiddle.first << "," << tileMiddle.second << std::endl;

}

void GemController::update(float dt)
{
  getState()->update(dt);
}

void GemController::draw()
{
  getState()->draw();
}

// @returns true, if gem became selected
// TODO this seems like a poor solution for some reason
bool GemController::onClicked()
{
  GemStates::GemState *state = getState()->onClicked();
  if (state) {
    setState(state);
    return true;
  }
  return false;
}
Board* GemController::getBoard()
{
  return m_pBoard;
}


GemController::~GemController()
{
  delete m_gem;
}
