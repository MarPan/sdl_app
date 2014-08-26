#include "moveinfo.h"

void MoveInfo::addRelocation(Relocation r)
{
  m_relocations.push_back(r);
}


void MoveInfo::addCreation(Coordinates c)
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

const std::vector<Relocation> MoveInfo::getRelocations() const
{
  return m_relocations;
}


const std::vector<Coordinates> MoveInfo::getCreations() const
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

