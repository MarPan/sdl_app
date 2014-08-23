#include "boardstate.h"

BoardState::BoardState()
{
}

BoardState::~BoardState()
{
}

IdleState::IdleState(Board *board)
  : m_pBoard(board)
{

}

void IdleState::onClick(int x, int y)
{

}

void IdleState::update(float dt)
{

}

void IdleState::draw()
{

}
