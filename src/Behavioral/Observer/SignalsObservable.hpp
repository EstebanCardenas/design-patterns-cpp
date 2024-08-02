/*
 * SignalsObservable.hpp
 *
 *  Created on: Aug 1, 2024
 *      Author: necar
 */

#pragma once

#include <boost/signals2.hpp>
#include <iostream>

using namespace std;
using namespace boost;

template <typename T>
struct ObservableTwo {
	signals2::signal<void(T&, const string&)> field_changed;
};

class ObPersonTwo: public ObservableTwo<ObPersonTwo> {
	int age;
public:
	int getAge() const {
		return age;
	}

	void setAge(int age) {
		if (this->age == age) return;
		this->age = age;
		field_changed(*this, "age");
	}
};

int ob2Main() {
	ObPersonTwo person;
	auto conn = person.field_changed.connect([](ObPersonTwo& p, const string& field) {
		cout << "Field " << field << " has changed." << endl;
	});
	person.setAge(30);
	conn.disconnect();
	person.setAge(15);

	return 0;
}
