/*
 * FunctionalDecorator.hpp
 *
 *  Created on: May 8, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <functional>
#include <iostream>

using namespace std;

typedef function<void()> VoidCallback;

struct Logger {
	VoidCallback func;
	string name;

	Logger(VoidCallback f, string name) : func(f), name(name) {}

	void operator()() const {
		cout << "Entering " << name << endl;
		func();
		cout << "Exiting " << name << endl;
	}
};

template <typename Func>
struct Logger2 {
	Func func;
	string name;

	Logger2(Func func, string name): func(func), name(name) {}

	void operator()() const {
		cout << "Entering " << name << endl;
		func();
		cout << "Exiting " << name << endl;
	}
};

template <typename Func>
auto make_logger2(Func func, string name) {
	return Logger2<Func>{func, name};
}

double add(int a, int b) {
	cout << a << " + " << b << " = " << (a+b) << endl;
	return a+b;
}

template <typename> struct Logger3;

template <typename R, typename ...Args>
struct Logger3<R(Args...)> {
	function<R(Args...)> func;
	string name;

	Logger3(function<R(Args...)> func, string name) : func(func), name(name) {}

	R operator()(Args... args) const {
		cout << "Entering " << name << endl;
		R result = func(args...);
		cout << "Exiting " << name << endl;
		return result;
	}
};

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const string& name) {
	return Logger3<R(Args...)>(
		function<R(Args...)>(func),
		name
	);
}

int functionalDecMain() {
	Logger logger{ []() { cout << "Hello World!" << endl; }, "hello_world" };
	logger();

	auto log = make_logger2([]() {
		cout << "Logger2" << endl;
	}, "logger_2");
	log();

	auto logged_add = make_logger3(add, "add");
	auto result = logged_add(2, 3);
	cout << "result = " << result << endl;
	return 0;
}
