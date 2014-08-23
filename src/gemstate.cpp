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
                         m_gem->getBoard()->getGemsOffset().first + m_gem->getPosition().first * m_gem->getSize().first,
                         m_gem->getBoard()->getGemsOffset().second + m_gem->getPosition().second * m_gem->getSize().second,
                         m_gem->getSize().first,
                         m_gem->getSize().second);
}
