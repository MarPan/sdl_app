#ifndef MOVEINFO_H
#define MOVEINFO_H

#include <vector>
#include "utilities.h"
#include "gemcontroller.h"

typedef std::pair<Coordinates, Coordinates> InvalidSwap;
typedef std::pair<Coordinates, Coordinates> Relocation;
typedef std::pair<Coordinates, Coordinates> Swap;

struct Creation
{
  Creation(int _x, int _y, GemType _type)
    : type(_type), first(_x), second(_y) { }
  GemType type;
  int first;
  int second;
  inline bool operator< (const Creation& rhs) const
  { return first < rhs.first; }
};

struct MoveInfo
{
public:
  void addRelocation(Relocation r);
  void addCreation(Creation c);
  void addAnnihilation(Coordinates a);
  void addInvalidSwap(InvalidSwap is);  
  void addSwap(Swap a);

  const std::vector<Relocation> getRelocations() const;
  const std::vector<Creation> getCreations() const;
  const std::vector<Coordinates> getAnnihilations() const;
  const std::vector<InvalidSwap> getInvalidSwaps() const;
  const std::vector<Swap> getSwaps() const;

private:
  std::vector<Relocation> m_relocations;
  std::vector<Creation> m_creations;
  std::vector<Coordinates> m_annihilations;
  std::vector<InvalidSwap> m_invalidSwaps;
  std::vector<Swap> m_swaps;
};

#endif // MOVEINFO_H
