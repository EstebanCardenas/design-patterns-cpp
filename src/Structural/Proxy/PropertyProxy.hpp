/*
 * PropertyProxy.hpp
 *
 *  Created on: May 15, 2024
 *      Author: necar
 */

#pragma once

#include <iostream>

using namespace std;

template <typename T>
struct Property {
	T value;

	Property(T v) {
		*this = v;
	}

	operator T() {
		return value;
	}

	T operator=(T new_value) {
		value = new_value;
		return value;
	}
};

struct Creature {
	Property<int> strength{10};
	Property<int> agility{5};
};

int propProxyMain() {
	Creature c;
	c.strength = 11;
	int x = c.agility;
	return 0;
}
