#pragma once

#include <array>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

class Creature
{
  enum Abilities { str, agl, intl, count };
  array<int, count> abilities;
public:
  int get_strength() const { return abilities[str]; }
  void set_strength(int value) { abilities[str] = value; }

  int get_agility() const { return abilities[agl]; }
  void set_agility(int value) { abilities[agl] = value; }

  int get_intelligence() const { return abilities[intl]; }
  void set_intelligence(int value) { abilities[intl] = value; }

  int sum() const {
    return accumulate(abilities.begin(), abilities.end(), 0);
  }

  double average() const {
    return sum() / (double)count;
  }

  int max() const {
    return *max_element(abilities.begin(), abilities.end());
  }
};

int creatureMain(int ac, char* av[])
{
  Creature orc;
  orc.set_strength(16);
  orc.set_agility(11);
  orc.set_intelligence(9);

  cout << "The orc has an average stat of "
       << orc.average()
       << " and a maximum stat of "
       << orc.max()
       << "\n";

  return 0;
}
