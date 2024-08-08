/*
 * TemplateMethod.hpp
 *
 *  Created on: Aug 6, 2024
 *      Author: necar
 */

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Game {
public:
	Game(int np): num_players{np} {}

	void run() {
		start();
		while (!have_winner()) {
			take_turn();
		}
		cout << "Player " << get_winner() << " wins!" << endl;
	}
protected:
	virtual void start() = 0;
	virtual bool have_winner() = 0;
	virtual void take_turn() = 0;
	virtual int get_winner() = 0;
	int current_player = 0;
	int num_players;
};

class Chess: public Game {
	int turn = 0, max_turns = 10;
public:
	Chess(): Game(2) {}
protected:
	void start() {
		cout << "Starting a game of chess with " << num_players << " players." << endl;
	}

	int get_winner() {
		return current_player;
	}

	bool have_winner() {
		return turn == max_turns;
	}

	void take_turn() {
		cout << "Turn " << turn << " taken by player " << current_player << endl;
		turn++;
		current_player = (current_player + 1) % num_players;
	}
};

int templateMethodMain() {
	Chess chess;
	chess.run();

	return 0;
}
