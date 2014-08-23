#include <iostream>
#include "gamestate.h"

GameState::GameState()
{
}

void GameState::onClick(int x, int y)
{
}

void GameState::update(int dt)
{
  std::cout << "Gamestate::update base method undefined";
}

void GameState::draw()
{
  std::cout << "Gamestate::draw base method undefined";
}
