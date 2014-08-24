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
  m_logicalCoords = std::make_pair(posX, posY);
  setSize(theTextureManager.getSize(m_texId));  
  computeDrawingOrign();
  setState(new GemStates::GemIdleState(this));
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
}

void Gem::draw()
{
  getState()->draw();
}

Board* Gem::getBoard()
{
  return m_pParent;
}

void Gem::computeDrawingOrign()
{
  std::pair<int,int> tileMiddle(getBoard()->getGemsOffset().first +
                                m_logicalCoords.second * getBoard()->getTileWidth(),
                                getBoard()->getGemsOffset().second +
                                m_logicalCoords.first * getBoard()->getTileWidth());

  tileMiddle.first -= m_size.first / 2;
  tileMiddle.second -= m_size.second / 2;

  setPosition(tileMiddle);
}


std::pair<int,int>Gem::getLogicalCoords()
{
  return m_logicalCoords;
}
void Gem::setLogicalCoords(std::pair<int,int> coords)
{
  m_logicalCoords = coords;
  computeDrawingOrign();
  setState(new GemStates::GemIdleState(this));
}