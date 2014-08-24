#include <iostream>
#include "board.h"
#include "gem.h"

Board::Board(int rows, int cols)
  : Object()
  , m_size(std::pair<int,int>(rows,cols))
  , m_backgroundPath("BackGround.jpg")
  , m_gemWidth(42)
  , m_gemsOffset(std::pair<int,int>(345,125))
{
  setState(new BoardStates::IdleState(this));
  m_boardLogic = new BoardLogic();
  m_boardLogic->resetBoard(8,8);
  m_gems = std::vector<std::vector<Gem*>>(8, 8);

  for (int i = 0; i < Gem::GT_COUNT; i++) {
    std::string path;
    switch (i) {
      case Gem::GT_BLUE:
        path = "Blue.png";
        break;
      case Gem::GT_GREEN:
        path = "Green.png";
        break;
      case Gem::GT_PURPLE:
        path = "Purple.png";
        break;
      case Gem::GT_RED:
        path = "Red.png";
        break;
      case Gem::GT_YELLOW:
        path = "Yellow.png";
        break;
    }
    m_gemRegistry.insert(std::make_pair(Gem::GemType(i), path));
    theTextureManager.load(path, path);
  }
  theTextureManager.load(m_backgroundPath, m_backgroundPath);

  updateBoard(m_boardLogic->dumpBoardState());
  // TODO
}

Board::~Board()
{
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)
      delete m_gems[i][j];
}

void Board::updateBoard(std::shared_ptr<MoveInfo> moveInfo)
{
  // firstly, we need a copy of our gems board
  // in this copy, we will execute all moves - instantly
  // next, in real board we tell all the gems how they should change 
  // and how should they render it

  // I hope I didn't understand this properly, because to me this kinda sucks

  // Why can't we simply iterate over every move
  // and instantly tell every gem what his destination and mode of move 
  // should be?

  for each (auto& swap in moveInfo->getSwaps())
  {
    std::pair<int,int> src = swap.getSource();
    std::pair<int,int> dst = swap.getDestination();

    std::swap(m_gems[src.first][src.second], m_gems[dst.first][dst.second]);
    m_gems[src.first][src.second]->m_logicalDestinationCoords = (src);
    m_gems[dst.first][dst.second]->m_logicalDestinationCoords = (dst);

    //m_gems[src.first][src.second]->setDestination();  r( GetGemAt( dst ) ) );
    //m_gems[dst.first][dst.second].Reset( Fx::GemPtr( GetGemAt( src ) ) );
  }

  for each ( auto& reloc in moveInfo->getRelocations())
  {
    std::pair<int,int> oldPos = reloc.getOldPosition();
    std::pair<int,int> newPos = reloc.getNewPosition();

    delete m_gems[newPos.first][newPos.second];
    m_gems[newPos.first][newPos.second] = m_gems[oldPos.first][oldPos.second];
    m_gems[oldPos.first][oldPos.second] = nullptr;
    m_gems[newPos.first][newPos.second]->m_logicalDestinationCoords = (newPos);
  } 


  for each (auto& newGem in moveInfo->getNewGems())
  {
    std::pair<int,int> coords = newGem.getPosition();
    delete m_gems[coords.first][coords.second]; // ?
    m_gems[coords.first][coords.second] = new Gem(coords.first, coords.second,
                                                  newGem.getGemType(), this);
  }
 /*
  for ( size_t i = 0; i < rows; ++i )
  {
    for ( size_t j = 0; j < cols; ++j )
    {
      GetGemBoxAt( i, j )->SetGem( copy[i][j] );
    }
  }

  for each ( auto& swap in moveInfo->GetSwaps() )
  {
    std::pair<int,int> src = swap.GetSource();
    std::pair<int,int> dst = swap.GetDestination();
    GetGemBoxAt( src )->RenderSwap();
    GetGemBoxAt( dst )->RenderSwap();
  }

  for each ( auto& reloc in moveInfo->GetRelocations() )
  {
    std::pair<int,int> newPos = reloc.GetNewPosition();
    GetGemBoxAt( newPos )->RenderDrop();
  }

  for each ( auto& newGem in moveInfo->GetNewGems() )
  {
    std::pair<int,int> cell = newGem.GetPosition();            
    GetGemBoxAt( cell )->RenderDrop();
  }

  for each ( auto& invalidSwap in moveInfo->GetInvalidSwaps() )
  {
    std::pair<int,int> src = invalidSwap.GetPosition();
    std::pair<int,int> dst = invalidSwap.GetInvalidNewPosition();
    GetGemBoxAt( src )->RenderInvalidSwap( GetCellPosition( dst ) );
    GetGemBoxAt( dst )->RenderInvalidSwap( GetCellPosition( src ) );
  }

  if ( !moveInfo->IsEmpty() )
  {
    m_moveStarted = true;
  }*/
}

//void Board::fillBoard()
//{
//  for (size_t i = 0; i < m_gems.size(); i++)
//    for (size_t j = 0; j < m_gems[i].size(); j++)
//      m_gems[i][j]->setType(Gem::GemType(rand() % Gem::GT_COUNT));
//}

bool Board::swapGems(std::pair<int,int> gemOne, std::pair<int,int> gemTwo)
{
  std::cout << "swapping " << gemOne.first << " " << gemOne.second
            << " with " << gemTwo.first << " " << gemTwo.second << std::endl;
  {
  auto tmp = m_gems[gemOne.first][gemOne.second]->getLogicalCoords();  
  m_gems[gemOne.first][gemOne.second]->setLogicalCoords(m_gems[gemTwo.first][gemTwo.second]->getLogicalCoords());
  m_gems[gemTwo.first][gemTwo.second]->setLogicalCoords(tmp);
  }
  
  Gem *tmp = m_gems[gemOne.first][gemOne.second];
  m_gems[gemOne.first][gemOne.second] = m_gems[gemTwo.first][gemTwo.second];
  m_gems[gemTwo.first][gemTwo.second] = tmp;

  return true;
}

void Board::update(float dt)
{
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)
      m_gems[i][j]->update(dt);
}

void Board::draw()
{
  theTextureManager.draw(m_backgroundPath, 0, 0, 755, 600);
  for (size_t i = 0; i < m_gems.size(); i++)
    for (size_t j = 0; j < m_gems[i].size(); j++)
      m_gems[i][j]->draw();
}

Gem *Board::getGem(int x, int y)
{
  return m_gems[x][y];
}

void Board::onClick(int x, int y)
{
  BoardStates::BoardState* state = getState()->onClick(x,y);
  if (state != nullptr) {
    setState(state);
  }
}

std::pair<int,int> Board::getGemsOffset()
{
  return m_gemsOffset;
}

int Board::getTileWidth()
{
  return m_gemWidth;
}

std::pair<int,int> Board::getSize()
{
  return m_size;
}

std::string Board::getGemPath(Gem::GemType gt)
{
  return m_gemRegistry[gt];
}

void Board::setSelectedGem(std::pair<int,int> coords)
{
  m_selectedGem = coords;
}

BoardLogic* Board::getLogic()
{
  return m_boardLogic;
}

std::pair<int,int> Board::getSelectedGem() const
{
  return m_selectedGem;
}