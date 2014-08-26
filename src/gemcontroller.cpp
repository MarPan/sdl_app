#include <iostream>
#include "gemcontroller.h"
#include "board.h"

GemController::GemController(int x, int y, Board* board)
  : m_gem(new Object())
  , m_pBoard(board)
{
  setCoords(std::make_pair(x, y));
  setState(new GemStates::GemIdleState(m_gem));
  m_gem->registerObserver(ObjectEvent::DESTINATION_REACHED,
                          std::bind(&GemController::onGemReachedDestination, this));
  // do we need to unregister, ever? I don't think so.

  if (x == 0 && y == 0) {
    m_gem->setRotation(180, 360);
  }
}

void GemController::setCoords(Coordinates coords)
{
  //std::cout << "Set coords called \n" ;
  m_logicalCoords = coords;
  m_gem->setPosition(computePosition(coords));
}


void GemController::addMoveTo(Coordinates coords)
{
  //std::cout << "From (" << m_logicalCoords.first << "," << m_logicalCoords.second << ") to " << "(" << coords.first << "," << coords.second << ")\n";;
  m_logicalCoords = coords;
  Coordinates destination = computePosition(coords);
  m_gem->addDestination(destination);
}

void GemController::setType(GemType type)
{
  m_type = type;
  m_gem->setTexId(m_pBoard->getGemPath(m_type));
  m_gem->setPosition(computePosition(m_logicalCoords));  // because size might have changed
}

void GemController::onGemReachedDestination()
{
  m_pBoard->gemFinishedMoving(this);
}

Coordinates GemController::computePosition(Coordinates coords)
{
  Coordinates tileMiddle(getBoard()->getGemsOffset().first +
                                coords.first * getBoard()->getTileWidth(),
                                getBoard()->getGemsOffset().second +
                                coords.second * getBoard()->getTileWidth());

  tileMiddle.first -= m_gem->getSize().first / 2;
  tileMiddle.second -= m_gem->getSize().second / 2;

  return tileMiddle;
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
  std::cout << "(" << m_logicalCoords.first << "," << m_logicalCoords.second << ")" << std::endl;
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
