/*
 * PointerChain.hpp
 *
 *  Created on: May 23, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <iostream>

using namespace std;

struct Creature {
	string name;
	int attack, defense;

	Creature(string n, int a, int d): name(n), attack(a), defense(d) {}

	friend ostream& operator <<(ostream& os, const Creature& creature) {
		os << "name: " << creature.name << " attack: " << creature.attack << " defense: " << creature.defense;
		return os;
	}
};

class CreatureModifier {
	CreatureModifier* next = nullptr;
protected:
	Creature& creature;
public:
	CreatureModifier(Creature& creature): creature(creature) {}

	void add(CreatureModifier* modifier) {
		if (!next) {
			next = modifier;
			return;
		}
		next->add(modifier);
	}

	virtual void handle() {
		if (next) {
			next->handle();
		}
	}
};

class DoubleAttackModifier: public CreatureModifier {
public:
	DoubleAttackModifier(Creature& creature): CreatureModifier(creature) {}

	void handle() override {
		creature.attack *= 2;
		CreatureModifier::handle();
	}
};

class IncreaseDefenseModifier: public CreatureModifier {
public:
	IncreaseDefenseModifier(Creature& creature): CreatureModifier(creature) {}

	void handle() override {
		if (creature.attack <= 2) {
			creature.defense++;
		}
		CreatureModifier::handle();
	}
};

class NoBonusesModifier: public CreatureModifier {
public:
	NoBonusesModifier(Creature& creature): CreatureModifier{creature} {}

	void handle() override {}
};

int pointerChainMain() {
	Creature goblin{"Goblin", 1, 1};
	CreatureModifier root{goblin};
	DoubleAttackModifier am1{goblin};
	DoubleAttackModifier am2{goblin};
	IncreaseDefenseModifier dm{goblin};
	NoBonusesModifier curse{goblin};

	root.add(&curse);
	root.add(&am1);
	root.add(&am2);
	root.add(&dm);
	root.handle();

	cout << goblin << endl;

	return 0;
}
