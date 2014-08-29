#include <iostream>
#include "gamestate.h"

GameState::GameState()
{
}

GameState::~GameState()
{ }

void GameState::update(float dt)
{
  //std::cout << "Gamestate::update base method undefined" << std::endl;
}

void GameState::draw()
{
  //std::cout << "Gamestate::draw base method undefined" << std::endl;
}

GameState* GameState::input(SDL_Event& event)
{
  return nullptr;
  //std::cout << "Gamestate::draw base method undefined" << std::endl;
}
