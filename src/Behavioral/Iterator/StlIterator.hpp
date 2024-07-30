/*
 * StlIterator.hpp
 *
 *  Created on: Jun 11, 2024
 *      Author: necar
 */

#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int stlItMain() {
	vector<string> names = {"Jack", "Jill", "John", "Jane"};
	vector<string>::iterator it = names.begin();
	cout << "Standard order:" << endl;
	while (it != names.end()) {
		string name = *it;
		cout << name << endl;
		it++;
	}

	cout << endl << "Reversed order:" << endl;
	vector<string>::reverse_iterator it2 = names.rbegin();
	while (it2 != names.rend()) {
		string name = *it2;
		cout << name << endl;
		it2++;
	}

	return 0;
}
