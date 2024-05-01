/*
 * Person.cpp
 *
 *  Created on: Apr 24, 2024
 *      Author: necar
 */

#include <iostream>

#include "Person.hpp"

void BclassImpl::greet(Bclass* person) {
	std::cout << "Hello " << person->name << std::endl;
}

Bclass::Bclass() :
	impl(new BclassImpl{}) {

}

Bclass::~Bclass() {
	delete impl;
}

void Bclass::greet() {
	impl->greet(this);
}
