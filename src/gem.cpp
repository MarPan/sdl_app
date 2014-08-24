#include <iostream>
#include "gem.h"
#include "board.h"
#include "texturemanager.h"
#include "gemstate.h"

Gem::Gem(int posX, int posY, GemType type, Board *parent)
  : m_type(type)
  , m_pParent(parent)
{
  setTexId(parent->getGemPath(type));
  setLogicalCoords(std::make_pair(posX, posY));
  setSize(theTextureManager.getSize(m_texId));
  setPosition(computeDrawingOrign(m_logicalCoords));
  setState(new GemStates::GemIdleState(this));
  std::cout  << " " << m_logicalCoords.first << " " << m_logicalCoords.second <<
               " " << m_logicalCoords.first << " " << m_logicalCoords.second << std::endl;
}

// @returns true, if gem became selected
// TODO this seems like a poor solution for some reason
bool Gem::onClicked()
{
  GemStates::GemState *state = getState()->onClicked();
  if (state) {
    setState(state);
    return true;
  }
  return false;  
}

void Gem::setType(GemType type)
{
  m_type = type;
}

void Gem::update(float dt)
{  
  getState()->update(dt);
  if (m_logicalDestinationCoords != m_logicalCoords) {
    std::cout << "setting movement dest " << m_logicalDestinationCoords.first << " " << m_logicalDestinationCoords.second << std::endl;
    std::cout << "setting movement src " << m_logicalCoords.first << " " << m_logicalCoords.second << std::endl;
    m_movementDestination = computeDrawingOrign(m_logicalDestinationCoords);
    std::cout << "setting movement dest " << m_movementDestination.first << " " << m_movementDestination.second << std::endl;
    std::cout << "setting movement src " << m_position.first << " " << m_position.second << std::endl;
    m_logicalCoords = m_logicalDestinationCoords;
    //TODO: set state to MOVING or sth
  }
  Object::update(dt);
}

void Gem::draw()
{
  getState()->draw();
}

Board* Gem::getBoard()
{
  return m_pParent;
}

std::pair<int,int> Gem::computeDrawingOrign(std::pair<int,int> logicalCoords)
{
  std::pair<int,int> tileMiddle(getBoard()->getGemsOffset().first +
                                logicalCoords.second * getBoard()->getTileWidth(),
                                getBoard()->getGemsOffset().second +
                                logicalCoords.first * getBoard()->getTileWidth());

  tileMiddle.first -= m_size.first / 2;
  tileMiddle.second -= m_size.second / 2;

  //setPosition(tileMiddle);
  return tileMiddle;
}


std::pair<int,int>Gem::getLogicalCoords()
{
  return m_logicalCoords;
}
void Gem::setLogicalCoords(std::pair<int,int> coords)
{
  m_logicalCoords = coords;
  m_logicalDestinationCoords = coords;
  setPosition(computeDrawingOrign(coords));
  setState(new GemStates::GemIdleState(this));
}