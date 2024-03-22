/*
 * AfMain.hpp
 *
 *  Created on: Mar 21, 2024
 *      Author: necar
 */

#pragma once

#include "DrinkFactory.hpp"
#include "FunctionalFactory.hpp"

void afMain() {
	DrinkWithVolumeFactory factory;
	auto drink = factory.make_drink("tea");
	drink->prepare(200);
}
