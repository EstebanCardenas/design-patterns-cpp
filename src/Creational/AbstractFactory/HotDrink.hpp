#pragma once

#include <iostream>

struct HotDrink {
	virtual ~HotDrink() = default;
	virtual void prepare(int volume) = 0;
};

struct Tea: HotDrink {
	void prepare(int volume) override {
		std::cout << "take tea bag" << std::endl;
		std::cout << "pour " << volume << std::endl;
	}
};

struct Coffee: HotDrink {
	void prepare(int volume) override {
		std::cout << "grind beans" << std::endl;
	}
};
