#include <iostream>
#include "gem.h"
#include "board.h"
#include "texturemanager.h"
#include "gemstate.h"

Gem::Gem(int posX, int posY, GemType type, Board *parent)
  : Object(posX, posY)
  , m_type(type)
  , m_pParent(parent)
{  
  setSize(m_pParent->getGemWidth());
  init();
}

void Gem::init()
{
  switch (m_type)
    {
    case GT_BLACK_AND_BLUE:
      m_texId = "chips\\chipBlueWhite.png";
      break;
    case GT_BLACK_AND_GREEN:
      m_texId = "chips\\chipGreenWhite.png";
      break;
    case GT_BLACK_AND_RED:
      m_texId = "chips\\chipRedWhite.png";
      break;
    case GT_BLACK_AND_WHITE:
      m_texId = "chips\\chipBlackWhite.png";
      break;
    }

  theTextureManager.load(m_texId, m_texId);
  m_size = theTextureManager.getSize(m_texId);
  setState(new GemIdleState(this));
}

void Gem::select()
{
  setState(new GemSelectedState(this));
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
