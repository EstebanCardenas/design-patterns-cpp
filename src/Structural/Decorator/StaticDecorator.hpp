/*
 * StaticDecorator.hpp
 *
 *  Created on: May 8, 2024
 *      Author: necar
 */

#pragma once

#include "DynamicDecorator.hpp"

template <typename T>
concept IsAShape = std::is_base_of<Shape, T>::value;

template <IsAShape T>
struct ColoredShape2: T {
	string color;

	ColoredShape2() {}

	template <typename ...Args>
	ColoredShape2(string color, Args ...args) : T(std::forward<Args>(args)...), color(color) {}

	string str() const override {
		ostringstream oss;
		oss << T::str() << " has the color " << color;
		return oss.str();
	}
};

int staticDecMain() {
	ColoredShape2<Circle> green_circle{"green", 5};
	cout << green_circle.str() << endl;
	return 0;
}
