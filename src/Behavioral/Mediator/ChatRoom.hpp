#pragma once
#include <algorithm>

struct ChatRoom
{
  vector<CrPerson*> people;

  void broadcast(const string& origin,
    const string& message);

  void join(CrPerson* p);

  void message(const string& origin,
    const string& who,
    const string& message)
  {
    auto target = std::find_if(
      begin(people),
      end(people),
      [&](const CrPerson *p) {
        return p->name == who;
      });
    if (target != end(people))
    {
      (*target)->receive(origin, message);
    }
  }
};


