#ifndef MOVEINFO_H
#define MOVEINFO_H

#include <vector>
#include "utilities.h"
#include "gemcontroller.h"

typedef std::pair<Coordinates, Coordinates> InvalidSwap;
typedef std::pair<Coordinates, Coordinates> Relocation;

struct Creation
{
  Creation(int _x, int _y, GemType _type)
    : type(_type), first(_x), second(_y) { }
  GemType type;
  int first;
  int second;
};

struct MoveInfo
{
public:
  void addRelocation(Relocation r);
  void addCreation(Creation c);
  void addAnnihilation(Coordinates a);
  void addInvalidSwap(InvalidSwap is);

  const std::vector<Relocation> getRelocations() const;
  const std::vector<Creation> getCreations() const;
  const std::vector<Coordinates> getAnnihilations() const;
  const std::vector<InvalidSwap> getInvalidSwaps() const;

private:
  std::vector<Relocation> m_relocations;
  std::vector<Creation> m_creations;
  std::vector<Coordinates> m_annihilations;
  std::vector<InvalidSwap> m_invalidSwaps;
};

#endif // MOVEINFO_H
