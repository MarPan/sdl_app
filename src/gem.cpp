#include "gem.h"
#include "texturemanager.h"

Gem::Gem()
{
  theTextureManager.load("../resources/chips/chipBlackWhite.png", "cbw");
}


void Gem::update(float dt)
{

}

void Gem::draw()
{
  theTextureManager.draw("obw", m_position.first, m_position.second, 40, 40);
}
