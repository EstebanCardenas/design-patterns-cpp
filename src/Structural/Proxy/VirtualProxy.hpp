/*
 * VirtualProxy.hpp
 *
 *  Created on: May 22, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <iostream>

using namespace std;

struct Image {
	virtual void draw() = 0;
};

struct Bitmap: Image {
	Bitmap(const string& filename) {
		cout << "Loading bitmap from " << filename << endl;
	}

	void draw() override {
		cout << "Drawing bitmap" << endl;
	}
};

class LazyBitmap: Image {
	string filename;
	Bitmap* bmp = nullptr;

public:
	LazyBitmap(const string& f): filename(f) {}

	void draw() override {
		if (!bmp) {
			bmp = new Bitmap{filename};
		}
		bmp->draw();
	}
};

int virtualProxyMain() {
	LazyBitmap bmp{"pokemon.png"};
	bmp.draw();
	return 0;
}
