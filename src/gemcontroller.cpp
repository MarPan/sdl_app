#include <iostream>
#include "gemcontroller.h"
#include "board.h"

GemController::GemController(int x, int y, Board* board)
  : m_gem(new Object())
  , m_pBoard(board)
  , m_removed(false)
{
  setCoords(std::make_pair(x, y));
  setState(new GemStates::GemIdleState(m_gem));
  m_gem->registerObserver(ObjectEvent::DESTINATION_REACHED,
                          std::bind(&GemController::onGemReachedDestination, this));
  m_gem->registerObserver(ObjectEvent::ROTATION_FINISHED,
                          std::bind(&GemController::onGemFinishedRotation, this));
  // do we need to unregister, ever? I don't think so.
}

void GemController::setCoords(Coordinates coords)
{
  //std::cout << "Set coords called \n" ;
  m_logicalCoords = coords;
  m_gem->setPosition(computePosition(coords));
}


void GemController::addMoveTo(Coordinates coords)
{
  std::cout << "From (" << m_logicalCoords.first << "," << m_logicalCoords.second << ") to " << "(" << coords.first << "," << coords.second << ")\n";;
  m_logicalCoords = coords;
  Coordinates destination = computePosition(coords);
  m_gem->addDestination(destination);
}

void GemController::setRotation(double angle, double speed)
{
  m_gem->setRotation(angle, speed);
}

void GemController::setType(GemType type)
{
  m_type = type;
  m_gem->setTexId(m_pBoard->getGemPath(m_type));
  m_gem->setPosition(computePosition(m_logicalCoords));  // because size might have changed
}

void GemController::onGemReachedDestination()
{
  if (!m_gem->isRotating()) {
    m_pBoard->gemFinishedMoving(this);
  }
}

void GemController::onGemFinishedRotation()
{
  if (!m_gem->isRotating()) {
    m_removed = true;  // right now rotation means that we are removing the gem.
    m_pBoard->gemFinishedMoving(this);
  }
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
  if (!m_removed) {
    getState()->draw();
  }
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

bool GemController::isSelected()
{
  return getState()->isSelected();
}

Board* GemController::getBoard()
{
  return m_pBoard;
}

void GemController::remove()
{  
  setRotation(180, 1440);
  // we should set m_removed only after rotation finishes
}

bool GemController::isRemoved()
{
  return m_removed;
}

Coordinates GemController::getCoordinates()
{
  return m_logicalCoords;
}

GemController::~GemController()
{
  delete m_gem;
}
