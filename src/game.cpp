#include <SDL2/SDL.h>
#include "utilities.h"
#include "game.h"
#include "texturemanager.h"

Game::Game()
  : _windowSize(std::pair<int, int>(640, 480)),
    _exit(false),
    _world(new World())
{
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

  _renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

  if (_renderer == NULL) {
    printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
  }

  theTextureManager.load("../resources/board.bmp", "board", _renderer);
  //background = loadTexturePlease("../resources/board.bmp", _renderer);

  // Game status
  _exit = false;
  _lastTime = SDL_GetTicks();
}

void Game::run(void)
{
  printf("STARTING LOOP:\n");
  while (_exit == false) {
      // At the start of a frame we want to start our FPS timer
      float deltaTime = (float)(SDL_GetTicks() - _lastTime) / 1000;
//      printf("%f\n", deltaTime);

      input();
      update(deltaTime);
      draw();

      // At the end of a frame we want to reset our frame timer
      _lastTime = SDL_GetTicks();
       SDL_Delay(10);  // what is this for?
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
  SDL_RenderClear(_renderer);
  theTextureManager.draw("board", 0, 0, _windowSize.first, _windowSize.second, _renderer);
  //SDL_RenderCopy(_renderer, background, NULL, NULL);
  _world->draw(_renderer);
  SDL_RenderPresent(_renderer);
}
