/*
 * Person.hpp
 *
 *  Created on: Apr 24, 2024
 *      Author: necar
 */

#pragma once

#include <string>

class BclassImpl;

class Bclass {
public:
	std::string name;

	BclassImpl* impl;

	Bclass();
	~Bclass();

	void greet();
};

class BclassImpl {
public:
	void greet(Bclass* person);
};
