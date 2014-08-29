#include "multiplatformSDL.h"
#include "utilities.h"
#include "game.h"
#include "board.h"
#include "texturemanager.h"
#include "playtimestate.h"
#include "clock.h"

Game::Game()
  : _windowSize(std::pair<int, int>(755, 600)),
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

  //initialize TTF
  if( TTF_Init() < 0 )
  {
      printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
  }
  SDL_ShowCursor(1);      // show cursor

  // Create window and renderer
  m_pWindow = SDL_CreateWindow("Pong",
          SDL_WINDOWPOS_UNDEFINED,        // centered window
          SDL_WINDOWPOS_UNDEFINED,        // centered window
          _windowSize.first,
          _windowSize.second,
          SDL_WINDOW_SHOWN);

  if (m_pWindow == NULL) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
  }

  m_pRenderer = SDL_CreateRenderer( m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

  if (m_pRenderer == NULL) {
    printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
  }

  // Game status
  _exit = false;
  _lastTime = SDL_GetTicks();

  setState(new PlayTimeState());
}

void Game::run(void)
{
  printf("STARTING LOOP:\n");
  Clock* c = new Clock();
  c->start(1);
  while (_exit == false) {
    float deltaTime = (float)(SDL_GetTicks() - _lastTime) / 1000;
//      printf("%f\n", deltaTime);
    input();
    update(deltaTime);
    draw();

    _lastTime = SDL_GetTicks();
    SDL_Delay(10);
  }
  c->stop();
  printf("THE END\n");
}

void Game::input()
{
  while (SDL_PollEvent(&event)) {
    switch (event.type)
    {
    // Clicking 'x' or pressing F4
    case SDL_QUIT:
      printf("GOT SDL_QUIT\n");
     _exit = true;
     break;
    case SDL_MOUSEBUTTONDOWN:
      switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            //SDL_ShowSimpleMessageBox(0, "Mouse", "Left button was pressed!", m_pWindow);
            getState()->onClick(event.button.x, event.button.y); // !!
            break;
        case SDL_BUTTON_RIGHT:
            //SDL_ShowSimpleMessageBox(0, "Mouse", "Right button was pressed!", m_pWindow);
            break;
        default:
            //SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", m_pWindow);
            break;
      }
      break;
    case SDL_USEREVENT:        
        getState()->input(event);
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
//  theTextureManager.draw("board", 0, 0, _windowSize.first, _windowSize.second);
  getState()->draw();
  SDL_RenderPresent(m_pRenderer);
}
