#include <iostream>
#include "gem.h"
#include "texturemanager.h"


void GemState::onEnter(Gem &gem)
{
  m_gem = &gem;
}

void GemState::draw()
{
  theTextureManager.draw(m_gem->getTexId(),
                         m_gem->getPosition().first * m_gem->getSize().first,
                         m_gem->getPosition().second * m_gem->getSize().second,
                         m_gem->getSize().first,
                         m_gem->getSize().second);
}

Gem::Gem(int posX, int posY, int width, GemType type)
  : Object(posX, posY),
    m_type(type)
{  
  setSize(width);
  init();
}

void Gem::init()
{
  switch (m_type)
    {
    case GT_BLACK_AND_BLUE:
      m_texId = "../resources/chips/chipBlueWhite.png";
      break;
    case GT_BLACK_AND_GREEN:
      m_texId = "../resources/chips/chipGreenWhite.png";
      break;
    case GT_BLACK_AND_RED:
      m_texId = "../resources/chips/chipRedWhite.png";
      break;
    case GT_BLACK_AND_WHITE:
      m_texId = "../resources/chips/chipBlackWhite.png";
      break;
    }

  theTextureManager.load(m_texId, m_texId);
  m_size = theTextureManager.getSize(m_texId);
  setState(new GemIdleState());
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
