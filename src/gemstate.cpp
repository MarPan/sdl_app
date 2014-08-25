#include <sstream>
#include <iostream>
#include "gemstate.h"
#include "texturemanager.h"
#include "gemcontroller.h"
#include "board.h"

namespace GemStates {

GemState::GemState(Object *gem)
  : m_gem(gem)
{ }

void GemState::draw()
{
  m_gem->draw();
}

void GemState::update(float dt)
{
  m_gem->update(dt);
}

GemState *GemState::onClicked()
{
  return nullptr  ;
}


GemSelectedState::GemSelectedState(Object *gem)
  : GemState(gem) 
  , m_circleName("leafcircle.png")
{
  theTextureManager.load(m_circleName, m_circleName);
  m_circle.setTexId(m_circleName);
  auto gemOrigin = m_gem->getPosition();
  auto gemSize =  m_gem->getSize();
  gemSize.first /= 2;
  gemSize.second /= 2;
  gemOrigin.first += gemSize.first;
  gemOrigin.second += gemSize.second;
  // now gemOrigin is the middle of a gem
  gemOrigin.first -= m_circle.getSize().first / 2;
  gemOrigin.second -= m_circle.getSize().second / 2;
  m_circle.setPosition(gemOrigin);
}

void GemSelectedState::draw()
{
  GemState::draw();
  m_circle.draw();
}

GemState* GemSelectedState::onClicked()
{
  return new GemStates::GemIdleState(m_gem);
}

GemIdleState::GemIdleState(Object *gem)
  : GemState(gem) 
{}

GemState* GemIdleState::onClicked()
{
  return new GemStates::GemSelectedState(m_gem);
}

}
