/*
 * Singleton.hpp
 *
 *  Created on: Apr 4, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

class IDatabase {
public:
	virtual int get_population(const std::string& name) = 0;
};

class Database: public IDatabase {
private:
	std::unordered_map<std::string, int> capitals;

	Database() {
		std::cout << "Init DB" << std::endl;
		capitals["Tokyo"] = 13000000;
		capitals["Motevideo"] = 8000000;
		capitals["Rome"] = 5000000;
	}
public:
	Database(Database const&) = delete;
	void operator=(Database const&) = delete;

	static Database& instance() {
		static Database db;
		return db;
	}

	int get_population(const std::string& name) override {
		if (capitals.count(name)) {
			return capitals[name];
		}
		return 0;
	}

	bool contains_city(const std::string& city) {
		return capitals.count(city);
	}
};

struct MockDatabase: public IDatabase {
	int get_population(const std::string& name) override {
		return 100;
	}
};

struct RecordFinder {
	IDatabase& db;

	RecordFinder(IDatabase& db) : db(db) {}

	int total_population(std::vector<std::string> names) {
		int result = 0;
		for (std::string name: names) {
			result += Database::instance().get_population(name);
		}
		return result;
	}
};

void singletonMain() {
	std::cout << Database::instance().get_population("Cali") << std::endl;
	RecordFinder rf{Database::instance()};
	std::cout << rf.total_population({"Tokyo", "Rome"});
}
