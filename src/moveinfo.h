#ifndef MOVEINFO_HPP
#define MOVEINFO_HPP

#include <vector>
#include "gem.h"

class MoveInfo
{
public:
  class Relocation
  {
  public:
    Relocation(const std::pair<int,int>& oldPosition,
                const std::pair<int,int>& newPosition);

    std::pair<int,int> getOldPosition() const;
    std::pair<int,int> getNewPosition() const;

  private:
    std::pair<int,int> m_oldPosition;
    std::pair<int,int> m_newPosition;
  };

  class NewGem
  {
  public:
    NewGem(const Gem::GemType& type, const std::pair<int,int>& position);

    std::pair<int,int> getPosition() const;
    Gem::GemType getGemType() const;

  private:
    Gem::GemType m_type;
    std::pair<int,int> m_position;
  };

  class Swap
  {
  public:
    Swap(const std::pair<int,int>& source,
      const std::pair<int,int>& destination);

    std::pair<int,int> getSource() const;
    std::pair<int,int> getDestination() const;

  private:
    std::pair<int,int> m_source;
    std::pair<int,int> m_destination;
  };

  class InvalidSwap
  {
  public:
    InvalidSwap(const std::pair<int,int>& position,
      const std::pair<int,int>& invalidNewPosition);

    std::pair<int,int> getPosition() const;
    std::pair<int,int> getInvalidNewPosition() const;

  private:
    std::pair<int,int> m_position;
    std::pair<int,int> m_invalidNewPosition;
  };

  class Connection
  {
  public:
    struct GemInfo
    {
      GemInfo(const std::pair<int,int>& coords_, const Gem::GemType& type_);
      std::pair<int,int> coords;
      Gem::GemType type;
    };

    void addGem(const std::pair<int,int>& coords, const Gem::GemType& gemType);
    const GemInfo& operator [](size_t index) const;
    size_t getSize() const;

  private:
    std::vector<GemInfo> m_gems;
  };
  
  void addConnection(const Connection& connection);
  void addNewGem(const NewGem& newGem);
  void addRelocation(const Relocation& relocation);
  void addSwap(const Swap& swap);
  void addInvalidSwap(const InvalidSwap& invalidSwap);

  const std::vector<Connection>& getConnections() const;
  const std::vector<NewGem>& getNewGems() const;
  const std::vector<Relocation>& getRelocations() const;
  const std::vector<Swap>& getSwaps() const;
  const std::vector<InvalidSwap>& getInvalidSwaps() const;

  bool hasConnections() const;
  bool hasSwaps() const;
  bool hasInvalidSwaps() const;
  bool hasRelocations() const;
  bool hasNewGems() const;
  bool isEmpty() const;

private:
  std::vector<NewGem> m_newGems;
  std::vector<Connection> m_connections;
  std::vector<Relocation> m_relocations;
  std::vector<Swap> m_swaps;
  std::vector<InvalidSwap> m_invalidSwaps;
};

#endif // MOVEINFO_HPP
