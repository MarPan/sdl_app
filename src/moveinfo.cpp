#include "moveinfo.h"

void MoveInfo::addConnection(const Connection& connection)
{
  m_connections.push_back(connection);
}

void MoveInfo::addNewGem(const NewGem& newGem)
{
  m_newGems.push_back(newGem);
}

void MoveInfo::addRelocation(const Relocation& relocation)
{
  m_relocations.push_back(relocation);
}

void MoveInfo::addSwap(const Swap& swap)
{
  m_swaps.push_back(swap);
}

void MoveInfo::addInvalidSwap(const InvalidSwap& invalidSwap)
{
  m_invalidSwaps.push_back(invalidSwap);
}

const std::vector<MoveInfo::Connection>& MoveInfo::getConnections() const
{
  return m_connections;
}

const std::vector<MoveInfo::NewGem>& MoveInfo::getNewGems() const
{
  return m_newGems;
}

const std::vector<MoveInfo::Relocation>& MoveInfo::getRelocations() const
{
  return m_relocations;
}

const std::vector<MoveInfo::Swap>& MoveInfo::getSwaps() const
{
  return m_swaps;
}

const std::vector<MoveInfo::InvalidSwap>& MoveInfo::getInvalidSwaps() const
{
  return m_invalidSwaps;
}

bool MoveInfo::hasConnections() const
{
  return !m_connections.empty();
}

bool MoveInfo::hasSwaps() const
{
  return !m_swaps.empty();
}

bool MoveInfo::hasInvalidSwaps() const
{
  return !m_invalidSwaps.empty();
}

bool MoveInfo::hasRelocations() const
{
  return !m_relocations.empty();
}

bool MoveInfo::hasNewGems() const
{
  return !m_newGems.empty();
}

bool MoveInfo::isEmpty() const
{
  return m_connections.empty() && m_newGems.empty() && m_relocations.empty();
}

MoveInfo::Relocation::Relocation(const std::pair<int,int>& oldPosition,
  const std::pair<int,int>& newPosition)
  : m_oldPosition(oldPosition)
  , m_newPosition(newPosition)
{

}

std::pair<int,int> MoveInfo::Relocation::getOldPosition() const
{
  return m_oldPosition;
}

std::pair<int,int> MoveInfo::Relocation::getNewPosition() const
{
  return m_newPosition;
}

MoveInfo::NewGem::NewGem(const Gem::GemType& type, const std::pair<int,int>& position)
  : m_type(type)
  , m_position(position)
{

}

std::pair<int,int> MoveInfo::NewGem::getPosition() const
{
  return m_position;
}

Gem::GemType MoveInfo::NewGem::getGemType() const
{
  return m_type;
}

MoveInfo::Swap::Swap(const std::pair<int,int>& source, const std::pair<int,int>& destination)
  : m_source(source)
  , m_destination(destination)
{

}

std::pair<int,int> MoveInfo::Swap::getSource() const
{
  return m_source;
}

std::pair<int,int> MoveInfo::Swap::getDestination() const
{
  return m_destination;
}

MoveInfo::InvalidSwap::InvalidSwap(const std::pair<int,int>& position,
  const std::pair<int,int>& invalidNewPosition)
  : m_position(position)
  , m_invalidNewPosition(invalidNewPosition)
{

}

std::pair<int,int> MoveInfo::InvalidSwap::getPosition() const
{
  return m_position;
}

std::pair<int,int> MoveInfo::InvalidSwap::getInvalidNewPosition() const
{
  return m_invalidNewPosition;
}

void MoveInfo::Connection::addGem( const std::pair<int,int>& coords, const Gem::GemType& gem )
{
  m_gems.push_back(GemInfo(coords, gem));
}

const MoveInfo::Connection::GemInfo& MoveInfo::Connection::operator [](size_t index) const
{
  return m_gems[index];
}

size_t MoveInfo::Connection::getSize() const
{
  return m_gems.size();
}

MoveInfo::Connection::GemInfo::GemInfo(const std::pair<int,int>& coords_, const Gem::GemType& type_)
  : coords(coords_)
  , type(type_)
{ }