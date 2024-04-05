/*
 * Monostate.hpp
 *
 *  Created on: Apr 4, 2024
 *      Author: necar
 */

#pragma once

#include <iostream>

class Printer {
	static int id;
public:
	int getId() const {
		return id;
	}

	void setId(int value) {
		id = value;
	}
};
int Printer::id = 0;

int monostateMain() {
	Printer p1;
	p1.setId(10);
	std::cout << Printer{}.getId();
	return 0;
}
