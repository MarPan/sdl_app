#ifndef BOARDLOGIC_H
#define BOARDLOGIC_H

#include <vector>
#include "gemcontroller.h"
#include "moveinfo.h"

class BoardLogic
{
public:
  BoardLogic(int x, int y);
  void swapGems(Coordinates src, Coordinates dst, MoveInfo& moveInfo);
  void updateBoard(MoveInfo& moveInfo);
  /*
   * PS approach:
   * każdy ruch, każde cokolwiek na logicznej planszy generuje ruch
   * ruch jest opisywany przez MoveInfo
   *
   * Problem:
   * Użytkownik klika na planszy na drugi diament.
   * Wołam swapGems w BoardLogic
   *
   * Dostaję w odpowiedzi MoveInfo, do wykorzystania w Board, żeby wyświetlić animacje.
   *
   * Jak mi się skończy animacja, dopiero wtedy wołam updateBoard.
   *
   */


private:
  std::vector<std::vector<GemType>> m_logicBoard;
};

#endif // BOARDLOGIC_H
