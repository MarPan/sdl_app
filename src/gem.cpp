#include <iostream>
#include "gem.h"
#include "texturemanager.h"

Gem::Gem(std::pair<float,float> position)
  : Object(position)
{
  init();
}

Gem::Gem(float posX, float posY)
  : Object(posX, posY)
{
  init();
}

void Gem::init()
{
  theTextureManager.load("../resources/chips/chipBlackWhite.png", "cbw");
  m_size = theTextureManager.getSize("cbw");
}

void Gem::update(float dt)
{

}

void Gem::draw()
{
  theTextureManager.draw("cbw",
                         m_position.first * m_size.first,
                         m_position.second * m_size.second,
                         m_size.first, m_size.second);
}
