/*
 * ClassicState.hpp
 *
 *  Created on: Aug 4, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <iostream>

using namespace std;

struct LightSwitch;

struct State {
	virtual void on(LightSwitch* lhs) {
		cout << "Light is already on" << endl;
	}

	virtual void off(LightSwitch* lhs) {
		cout << "Light is already off" << endl;
	}
};

struct OnState: State {
	OnState() {
		cout << "Light is turned on" << endl;
	}

	void off(LightSwitch* lhs) override;
};

struct OffState: State {
	OffState() {
		cout << "Light is turned off" << endl;
	}

	void on(LightSwitch* lhs) override;
};

class LightSwitch {
	State* state;
public:
	LightSwitch() {
		state = new OffState{};
	}

	void set_state(State* state) {
		this->state = state;
	}

	void on() {
		state->on(this);
	}

	void off() {
		state->off(this);
	}
};

void OnState::off(LightSwitch* ls) {
	cout << "Switching light off" << endl;
	ls->set_state(new OffState{});
	delete this;
}

void OffState::on(LightSwitch* ls) {
	cout << "Switching light on" << endl;
	ls->set_state(new OnState{});
	delete this;
}

int clsStateMain() {
	LightSwitch ls;
	ls.on();
	ls.off();
	ls.off();

	return 0;
}
