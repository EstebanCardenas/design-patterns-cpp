#include "Person.hpp"
#include "ChatRoom.hpp"

int crMain()
{
  ChatRoom room;

  CrPerson john{"John"};
  CrPerson jane{"Jane"};
  room.join(&john);
  room.join(&jane);
  john.say("hi room");
  jane.say("oh, hey john");

  CrPerson simon{"Simon"};
  room.join(&simon);
  simon.say("hi everyone!");

  jane.pm("Simon", "glad you found us, simon!");

  return 0;
}
