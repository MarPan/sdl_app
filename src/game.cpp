#include <SDL2/SDL.h>
#include "utilities.h"
#include "game.h"
#include "board.h"
#include "texturemanager.h"

Game::Game()
  : _windowSize(std::pair<int, int>(640, 480)),
    _exit(false),
    _world(new World())
{
}

/*static*/ Game& Game::getInstance()
{
  static Game instance;
  return instance;
}

void Game::init()
{
  // Intialize SDL
  if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  }
  SDL_ShowCursor(1);      // show cursor

  // Create window and renderer
  window = SDL_CreateWindow("Pong",
          SDL_WINDOWPOS_UNDEFINED,        // centered window
          SDL_WINDOWPOS_UNDEFINED,        // centered window
          _windowSize.first,
          _windowSize.second,
          SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
  }

  m_pRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

  if (m_pRenderer == NULL) {
    printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
  }

  theTextureManager.load("../resources/board.bmp", "board");
  _world->add(new Board(8,8));

  // Game status
  _exit = false;
  _lastTime = SDL_GetTicks();
}

void Game::run(void)
{
  printf("STARTING LOOP:\n");
  while (_exit == false) {
    float deltaTime = (float)(SDL_GetTicks() - _lastTime) / 1000;
//      printf("%f\n", deltaTime);

    input();
    update(deltaTime);
    draw();

    _lastTime = SDL_GetTicks();
     SDL_Delay(10);
  }
  printf("THE END\n");
}

void Game::input()
{
  while (SDL_PollEvent(&event)) {
    // Clicking 'x' or pressing F4
    if (event.type == SDL_QUIT) {
      printf("GOT SDL_QUIT\n");
     _exit = true;
    }
  }
}

void Game::update(float deltaTime)
{
  _world->update(deltaTime);
}

void Game::draw()
{
  SDL_RenderClear(m_pRenderer);
  theTextureManager.draw("board", 0, 0, _windowSize.first, _windowSize.second);
  _world->draw();
  SDL_RenderPresent(m_pRenderer);
}
