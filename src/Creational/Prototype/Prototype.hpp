/*
 * Prototype.hpp
 *
 *  Created on: Apr 3, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <iostream>
#include <memory>

struct Address {
	std::string street, city;
	int suite;

	Address(std::string street, std::string city, int suite): street(street), city(city), suite(suite) {}

	Address(const Address& other) : street(other.street), city(other.city), suite(other.suite) {}
};

struct Contact {
	std::string name;
	Address* address;

	Contact(std::string name, Address* address) : name(name), address(address) {}

	Contact(const Contact& other) {
		name = other.name;
		address = new Address{ *other.address };
	}
};

struct EmployeeFactory {
	static std::unique_ptr<Contact> new_main_office_employee(const std::string& name, int suite) {
		Contact p{"", new Address{"123 East Dr", "London", 0}};
		return new_employee(name, suite, p);
	}
private:
	static std::unique_ptr<Contact> new_employee(const std::string name, int suite, const Contact& prototype) {
		std::unique_ptr<Contact> result = std::make_unique<Contact>(prototype);
		result->name = name;
		result->address->suite = suite;
		return result;
	}
};

int protoMain() {
	std::unique_ptr<Contact> john = EmployeeFactory::new_main_office_employee("john", 123);
	std::unique_ptr<Contact> jane = EmployeeFactory::new_main_office_employee("jane", 99);
	std::cout << john->name << " " << john->address->suite;
	std::cout << jane->name << " " << jane->address->suite;
	return 0;
}
