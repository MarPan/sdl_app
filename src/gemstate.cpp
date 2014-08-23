#include <sstream>
#include <iostream>
#include "gemstate.h"
#include "texturemanager.h"
#include "gem.h"
#include "board.h"

GemState::GemState(Gem *gem)
  : m_gem(gem)
{ }

void GemState::draw()
{
  theTextureManager.draw(m_gem->getTexId(),
                         m_gem->getPosition().first,
                         m_gem->getPosition().second,
                         m_gem->getSize().first,
                         m_gem->getSize().second);
}


GemSelectedState::GemSelectedState(Gem *gem) 
  : GemState(gem) 
  , m_circleName("leafcircle.png")
{
  theTextureManager.load(m_circleName, m_circleName);
  m_circle.setTexId(m_circleName);
  m_circle.setSize(theTextureManager.getSize(m_circleName));
  auto gemOrigin = m_gem->getPosition();
  auto gemSize =  m_gem->getSize();
  gemSize.first /= 2;
  gemSize.second /= 2;
  gemOrigin.first += gemSize.first;
  gemOrigin.second += gemSize.second;
  // now gemOrigin is the middle of a gem
  gemOrigin.first -= m_circle.getSize().first/2;
  gemOrigin.second -= m_circle.getSize().second/2;
  m_circle.setPosition(gemOrigin);
}

void GemSelectedState::draw()
{
  GemState::draw();
  theTextureManager.draw(m_circleName,
                         m_circle.getPosition().first,
                         m_circle.getPosition().second,
                         m_circle.getSize().first,
                         m_circle.getSize().second);
}