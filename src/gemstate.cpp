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
  : GemState(gem) {}

void GemSelectedState::draw()
{
}