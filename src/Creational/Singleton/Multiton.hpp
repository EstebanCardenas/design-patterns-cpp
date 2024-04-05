/*
 * Multiton.hpp
 *
 *  Created on: Apr 4, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>

enum class Importance {
	primary, secondary, tertiary
};

template <typename T, typename K = std::string>
class Multiton {
private:
	static std::unordered_map<K, std::shared_ptr<T>> instances;
protected:
	Multiton() = default;
	virtual ~Multiton() = default;
public:
	static std::shared_ptr<T> get(const K& key) {
		if (instances.count(key)) {
			return instances[key];
		}
		auto instance = std::make_shared<T>();
		instances[key] = instance;
		return instance;
	}
};

template <typename T, typename K>
std::unordered_map<K, std::shared_ptr<T>> Multiton<T, K>::instances;

class Printer {
private:
	static int total_instance_cnt;
public:
	Printer() {
		++Printer::total_instance_cnt;
		std::cout << "A total of  " << Printer::total_instance_cnt << " instances so far.\n";
	}
};
int Printer::total_instance_cnt = 0;

int multitonMain() {
	typedef Multiton<Printer, Importance> mt;
	auto main = mt::get(Importance::primary);
	auto aux = mt::get(Importance::secondary);
	auto ter = mt::get(Importance::tertiary);
	auto ter2 = mt::get(Importance::tertiary);
	return 0;
}
