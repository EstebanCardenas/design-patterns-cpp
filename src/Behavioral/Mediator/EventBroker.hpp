/*
 * EventBroker.hpp
 *
 *  Created on: Jul 29, 2024
 *      Author: necar
 */

#pragma once

#include <boost/signals2.hpp>
#include <functional>
#include <string>
#include <iostream>

using namespace boost;
using namespace std;

struct EventData {
	virtual void print() const = 0;
};

struct PlayerScoreData: EventData {
	string player_name;
	int goals_scored;

	PlayerScoreData(const string& n, int g): player_name(n), goals_scored(g) {}

	void print() const override {
		cout << player_name << " has scored! goals scored: " << goals_scored << endl;
	}
};

struct Game {
	signals2::signal<void(EventData*)> events;
};

struct Player {
	string name;
	int goals_scored = 0;
	Game& game;

	Player(const string& n, Game& g): name(n), game{g} {}

	void score() {
		goals_scored++;
		PlayerScoreData ps{name, goals_scored};
		game.events(&ps);
	}
};

struct Coach {
	Coach(Game& game) {
		game.events.connect([](EventData* e) {
			PlayerScoreData* ps = dynamic_cast<PlayerScoreData*>(e);
			if (ps && ps->goals_scored < 3) {
				cout << "Coach says: well done, " << ps->player_name << "!\n";
			}
		});
	}
};

int evtBrokerMain() {
	Game game;
	Player player{"sam", game};
	Coach coach{game};

	player.score();
	player.score();
	player.score();

	return 0;
}
