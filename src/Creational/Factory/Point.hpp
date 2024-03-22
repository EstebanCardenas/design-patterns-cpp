#pragma once

#include <iostream>
#include <cmath>

enum class PointType {
	cartesian, polar
};

class Point {
	Point(float x, float y) {
		this->x = x;
		this->y = y;
	}

	// Inner class Factory
	struct InnerPointFactory {
		static Point NewCartesian(float x, float y) {
			return {x, y};
		}

		static Point NewPolar(float r, float theta) {
			return {
				r * std::cos(theta),
				r * std::sin(theta)
			};
		}
	};
public:
	float x, y;

	// Factory methods
	static Point NewCartesian(float x, float y) {
		return {x, y};
	}

	static Point NewPolar(float r, float theta) {
		return {
			r * std::cos(theta),
			r * std::sin(theta)
		};
	}

	static InnerPointFactory factory;

	friend class OuterPointFactory;
};

// Class Factory
struct OuterPointFactory {
	static Point NewCartesian(float x, float y) {
		return {x, y};
	}

	static Point NewPolar(float r, float theta) {
		return {
			r * std::cos(theta),
			r * std::sin(theta)
		};
	}
};

int pointMain() {
	Point p = Point::factory.NewCartesian(1, 2);
	std::cout << p.x;
	return 0;
}
