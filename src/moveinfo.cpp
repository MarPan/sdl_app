#include "moveinfo.h"

void MoveInfo::addRelocation(Relocation r)
{
  m_relocations.push_back(r);
}


void MoveInfo::addCreation(Creation c)
{
  m_creations.push_back(c);
}

void MoveInfo::addAnnihilation(Coordinates a)
{
  m_annihilations.push_back(a);
}

void MoveInfo::addInvalidSwap(InvalidSwap is)
{
  m_invalidSwaps.push_back(is);
}

void MoveInfo::addSwap(Swap s)
{
  m_swaps.push_back(s);
}

const std::vector<Relocation> MoveInfo::getRelocations() const
{
  return m_relocations;
}

const std::vector<Creation> MoveInfo::getCreations() const
{
  return m_creations;
}

const std::vector<Coordinates> MoveInfo::getAnnihilations() const
{
  return m_annihilations;
}

const std::vector<InvalidSwap> MoveInfo::getInvalidSwaps() const
{
  return m_invalidSwaps;
}

const std::vector<Swap> MoveInfo::getSwaps() const
{
  return m_swaps;
}
