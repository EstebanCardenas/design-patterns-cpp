/*
 * Composite.hpp
 *
 *  Created on: May 1, 2024
 *      Author: necar
 */

#pragma once

#include <iostream>
#include <vector>

struct GraphicObject {
	virtual void draw() = 0;
};

struct Circle: GraphicObject {
	void draw() override {
		std::cout << "Circle" << std::endl;
	}
};

struct Group: GraphicObject {
	std::string name;
	std::vector<GraphicObject*> objects;

	Group(const std::string& name) : name(name) {}

	void draw() override {
		std::cout << "Group " << name << " contains:" << std::endl;
		for (GraphicObject* obj: objects) {
			obj->draw();
		}
	}
};

int compositeMain() {
	Group root("root");
	Circle c1, c2;
	root.objects.push_back(&c1);
	root.objects.push_back(&c2);

	Group subgroup("sub");
	subgroup.objects.push_back(&c2);

	root.objects.push_back(&subgroup);
	root.draw();
	return 0;
}
