/*
 * Observer.hpp
 *
 *  Created on: Aug 1, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct Observer {
	virtual void field_changed(
	    T& source,
		const string& field
	) = 0;
};

template <typename T>
class Observable {
	vector<Observer<T>*> observers;
public:
	void notify(T& source, const string& field) {
		for (auto obs: observers) {
			obs->field_changed(source, field);
		}
	}

	void subscribe(Observer<T>* obs) {
		observers.push_back(obs);
	}

	void unsubscribe(Observer<T>* obs) {
		auto it = observers.begin();
		while (it != observers.end()) {
			if (*it == obs) {
				break;
			}
			it++;
		}
		if (it == observers.end()) return;
		observers.erase(it);
	}
};

class ObPerson: public Observable<ObPerson> {
	int age;
public:
	int get_age() {
		return age;
	}

	void set_age(int value) {
		if (age == value) return;

		age = value;
		notify(*this, "age");
	}
};

class ObPersonObserver: public Observer<ObPerson> {
	void field_changed(ObPerson& source, const string& field) {
		cout << "Person's " << field << " has changed" << endl;
	}
};

int obMain() {
	ObPerson person;
	ObPersonObserver obs;

	person.subscribe(&obs);
	person.set_age(20);
	person.unsubscribe(&obs);
	person.set_age(22);
	return 0;
}
