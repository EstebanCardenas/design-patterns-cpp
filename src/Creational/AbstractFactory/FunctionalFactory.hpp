/*
 * FunctionalFactory.hpp
 *
 *  Created on: Mar 21, 2024
 *      Author: necar
 */

#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

#include "HotDrink.hpp"

class DrinkWithVolumeFactory {
	std::unordered_map< std::string, std::function<std::unique_ptr<HotDrink>()> > factories;
public:
	DrinkWithVolumeFactory() {
		factories["tea"] = []() {
			auto tea = std::make_unique<Tea>();
			tea->prepare(200);
			return tea;
		};
		factories["coffee"] = []() {
			auto coffee = std::make_unique<Coffee>();
			coffee->prepare(50);
			return coffee;
		};
	}

	std::unique_ptr<HotDrink> make_drink(std::string str) {
		return factories[str]();
	}
};
