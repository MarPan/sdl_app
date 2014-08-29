#include "multiplatformSDL.h"
#include "utilities.h"
#include "game.h"
#include "board.h"
#include "gameoverstate.h"
#include "playtimestate.h"
#include "clock.h"

Game::Game()
  : _windowSize(std::pair<int, int>(755, 600)),
    _exit(false)
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
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }

  //initialize TTF
  if( TTF_Init() < 0 )
  {
      printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
  }
  SDL_ShowCursor(1);      // show cursor

  // Create window and renderer
  m_pWindow = SDL_CreateWindow("SDL_app",
          SDL_WINDOWPOS_UNDEFINED,        // centered window
          SDL_WINDOWPOS_UNDEFINED,        // centered window
          _windowSize.first,
          _windowSize.second,
          SDL_WINDOW_SHOWN);

  if (m_pWindow == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (m_pRenderer == NULL) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  // Game status
  _exit = false;
  _lastTime = SDL_GetTicks();

  setState(new PlayTimeState());
//  setState(new GameOverState(200));
}

void Game::run(void)
{
  printf("STARTING LOOP:\n");
  while (_exit == false) {
    float deltaTime = (float)(SDL_GetTicks() - _lastTime) / 1000;
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
    switch (event.type) {
      case SDL_QUIT:
        printf("GOT SDL_QUIT\n");
       _exit = true;
       break;
      case SDL_MOUSEBUTTONDOWN:
      case SDL_USEREVENT:
         GameState* state = getState()->input(event);
         if (state != nullptr) {
           setState(state);
         }
         break;
    }
  }
}

void Game::update(float deltaTime)
{
  getState()->update(deltaTime);
}

void Game::draw()
{
  SDL_RenderClear(m_pRenderer);
  getState()->draw();
  SDL_RenderPresent(m_pRenderer);
}

Game::~Game()
{
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}
