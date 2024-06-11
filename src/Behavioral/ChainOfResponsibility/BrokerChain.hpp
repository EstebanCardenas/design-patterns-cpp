/*
 * BrokerChain.hpp
 *
 *  Created on: May 23, 2024
 *      Author: necar
 */

#pragma once

#include <boost/signals2.hpp>

// Event broker (CoR + Observer + cqs)

using namespace boost;

struct Query {
	string creature_name;
	enum Argument {
		attack, defense
	} argument;
	int result;

	Query(const string& name, Argument argument, int result):
		creature_name(name), argument(argument), result(result) {}
};

struct Game { // mediator
	signals2::signal<void(Query&)> queries;
};

struct Creature {
	Game& game;
	int attack, defense;
	string name;
public:
	Creature(Game& g, int a, int d, string n):
		game(g), attack(a), defense(d), name(n) {}

	int get_attack() const {
		Query q{name, Query::Argument::attack, attack};
		game.queries(q);
		return q.result;
	}

	friend ostream& operator<<(ostream& os, const Creature& creature) {
		os << "name: " << creature.name << endl;
		os << "attack: " << creature.get_attack() << endl;
		// os << "defense: " << creature.defense << endl;
		return os;
	}
};

class CreatureModifier {
	Game& game;
	Creature& creature;
public:
	CreatureModifier(Game& g, Creature& c):
		game(g), creature(c) {}

	virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier: public CreatureModifier {
	signals2::connection conn;
public:
	DoubleAttackModifier(Game& g, Creature& c): CreatureModifier{g, c} {
		conn = g.queries.connect([&](Query& q) {
			if (q.creature_name == c.name &&
					q.argument == Query::Argument::attack) {
				q.result *= 2;
			}
		});
	}

	~DoubleAttackModifier() {
		conn.disconnect();
	}
};

int brokerChainMain() {
	Game game;
	Creature goblin{game, 2, 2, "Goblin"};
	cout << goblin;
	{
		DoubleAttackModifier dam{game, goblin};
		cout << goblin << endl;
	}

	cout << goblin << endl;

	return 0;
}
