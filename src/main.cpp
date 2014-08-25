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
  Object object;
  XXX xxx;
  object.registerObserver(ObjectEvent::DESTINATION_REACHED, std::bind(&XXX::foo, xxx));
  object.emitThisShit();
  std::cout.flush();
//  return 45;

  theGame.init();
  theGame.run();
  return 0;
}
