#include <iostream>
#include "gem.h"
#include "texturemanager.h"


void GemState::onEnter(Gem &gem)
{
  m_texId = gem.m_texId;
  m_positionAndSize.x = gem.m_position.first;
  m_positionAndSize.y = gem.m_position.second;
  m_positionAndSize.w = gem.m_size.first;
  m_positionAndSize.h = gem.m_size.second;
}

Gem::Gem(float posX, float posY)
  : Object(posX, posY),
    m_state(nullptr),
    m_texId("cbw")
{
  init();
}

void Gem::init()
{
  theTextureManager.load("../resources/chips/chipBlackWhite.png", m_texId);
  m_size = theTextureManager.getSize(m_texId);
  changeState(new GemIdleState());
}

void Gem::changeState(GemState *state)
{
  if (m_state) {
    m_state->onExit();
    delete m_state;
  }
  m_state = state;
  m_state->onEnter(*this);
}

void Gem::setType(GemType type)
{
  m_type = type;
}

void Gem::update(float dt)
{
  m_state->update(dt);
}

void Gem::draw()
{
  m_state->draw();
}
