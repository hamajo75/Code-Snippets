#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "person.h"
#include "chatroom.h"

/* Components should be unaware of each other.
 * Instead of components having references to each other, they are connected to 
 * Mediator.
 * Mediator: Facilitates communication between components, without them being aware
 *           of each other.
*/
//-------------------------------------------------------------------------------
int main() {
  ChatRoom room;

  auto john = std::make_shared<Person>("john");
  auto jane = std::make_shared<Person>("jane");

  room.join(john);
  room.join(jane);
  john->say("hi room");
  jane->say("oh, hey john");

  auto simon = std::make_shared<Person>("simon");
  room.join(simon);
  simon->say("hi everyone!");

  jane->privateMessaging("simon", "glad you could join us, simon");

  getchar();
  return 0;
}
