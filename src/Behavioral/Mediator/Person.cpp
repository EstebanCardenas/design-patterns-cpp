#include "Person.hpp"
#include "ChatRoom.hpp"
#include <iostream>

CrPerson::CrPerson(const string &name) : name(name) {}

void CrPerson::say(const string &message) const
{
  room->broadcast(name, message);
}

void CrPerson::pm(const string &who, const string &message) const
{
  room->message(name, who, message);
}

void CrPerson::receive(const string &origin, const string &message)
{
  string s = origin + ": \"" + message + "\"";
  std::cout << "[" << name << "'s chat session]" << s << "\n";
  chat_log.emplace_back(s);
}

bool CrPerson::operator==(const CrPerson &rhs) const {
  return name == rhs.name;
}

bool CrPerson::operator!=(const CrPerson &rhs) const {
  return !(rhs == *this);
}
