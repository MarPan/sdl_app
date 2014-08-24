#include <iostream>
#include "gamestate.h"

GameState::GameState()
{
}

void GameState::onClick(int x, int y)
{
  //std::cout << "Gamestate::onClick base method undefined (" << x << ", " << y << ")"  << std::endl;
}

void GameState::update(float dt)
{
  //std::cout << "Gamestate::update base method undefined" << std::endl;
}

void GameState::draw()
{
  //std::cout << "Gamestate::draw base method undefined" << std::endl;
}
