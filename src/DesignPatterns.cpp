//============================================================================
// Name        : DesignPatterns.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

#include "Structural/Decorator/FunctionalDecorator.hpp"

using namespace std;

int main() {
	string st = "Hello world";
	auto pos = st.find("world");
	if (pos != string::npos) {
		cout << "found" << endl;
	}

	return 0;
}
