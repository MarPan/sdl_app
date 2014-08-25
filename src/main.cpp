// no longer a pong game :)

#include <iostream>
#include "object.h"
#include "game.h"

class XXX {
public:
  void foo() {
    std::cout << x << "!" << std::endl;
  }
  int x = 34;
};

int main(int argc, char *argv[])
{
  theGame.init();
  theGame.run();
  return 0;
}
