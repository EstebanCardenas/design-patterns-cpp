/*
 * Shapes.hpp
 *
 *  Created on: May 8, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <cstdint>

using namespace std;

struct Shape {
	virtual string str() const = 0;
};

struct Circle: Shape {
	float radius;

	Circle() {}

	Circle(float radius): radius(radius) {}

	void resize(float factor) {
		radius *= factor;
	}

	string str() const override {
		ostringstream oss;
		oss << "A circle of radius " << radius;
		return oss.str();
	}
};

struct Square: Shape {
	float side;

	Square() {}

	Square(float side): side(side) {}

	string str() const override {
		ostringstream oss;
		oss << "A square with side " << side;
		return oss.str();
	}
};

struct ColoredShape: Shape {
	Shape& shape;
	string color;

	ColoredShape(Shape& shape, string color): shape(shape), color(color) {}

	string str() const override {
		ostringstream oss;
		oss << shape.str() << " has the color " << color;
		return oss.str();
	}
};

struct TransparentShape: Shape {
	Shape& shape;
	uint8_t transparency;

	TransparentShape(Shape& s, uint8_t t): shape(s), transparency(t) {}

	string str() const override {
		ostringstream oss;
		oss << shape.str() << " has "
				<< static_cast<float>(transparency) / 255.f * 100.f
				<< " % transparency";
		return oss.str();
	}
};

int shapesMain() {
	Square square{5};
	ColoredShape red_square{square, "red"};
	cout << square.str() << endl << red_square.str() << endl;

	TransparentShape my_square{red_square, 51};
	cout << my_square.str() << endl;
	return 0;
}
