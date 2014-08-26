#ifndef MOVEINFO_H
#define MOVEINFO_H

#include <vector>
#include "utilities.h"


typedef std::pair<Coordinates, Coordinates> InvalidSwap;
typedef std::pair<Coordinates, Coordinates> Relocation;

struct MoveInfo
{
public:
  void addRelocation(Relocation r);
  void addCreation(Coordinates c);
  void addAnnihilation(Coordinates a);
  void addInvalidSwap(InvalidSwap is);

  const std::vector<Relocation> getRelocations() const;
  const std::vector<Coordinates> getCreations() const;
  const std::vector<Coordinates> getAnnihilations() const;
  const std::vector<InvalidSwap> getInvalidSwaps() const;

private:
  std::vector<Relocation> m_relocations;
  std::vector<Coordinates> m_creations;
  std::vector<Coordinates> m_annihilations;
  std::vector<InvalidSwap> m_invalidSwaps;
};

#endif // MOVEINFO_H
