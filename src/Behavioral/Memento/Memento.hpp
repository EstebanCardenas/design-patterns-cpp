/*
 * Memento.hpp
 *
 *  Created on: Jul 30, 2024
 *      Author: necar
 */

#pragma once

#include <ostream>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Memento {
	int balance;
public:
	Memento(int b): balance{b} {}

	friend class MemBankAccount;
	friend class BankAccountTwo;
};

class MemBankAccount {
	int balance = 0;
public:
	MemBankAccount(int balance): balance(balance) {}

	Memento deposit(int amt) {
		balance += amt;
		return Memento{balance};
	}

	void restore(const Memento& memento) {
		balance = memento.balance;
	}

	friend ostream& operator<<(ostream& os, const MemBankAccount& acc) {
		os << "balance: " << acc.balance;
		return os;
	}
};

class BankAccountTwo {
	int balance = 0;
	vector<shared_ptr<Memento>> changes;
	int current; // Pointer to change
public:
	BankAccountTwo(int b): balance{b} {
		changes.emplace_back(make_shared<Memento>(balance));
		current = 0;
	}

	shared_ptr<Memento> deposit(int amt) {
		balance += amt;
		auto mem = make_shared<Memento>(balance);
		changes.emplace_back(mem);
		current++;
		return mem;
	}

	void restore(const shared_ptr<Memento>& mem) {
		if (!mem) return;

		balance = mem->balance;
		changes.push_back(mem);
		current = changes.size() - 1;
	}

	shared_ptr<Memento> undo() {
		if (current == 0) return {};

		auto mem = changes[--current];
		balance = mem->balance;
		return mem;
	}

	shared_ptr<Memento> redo() {
		if (current == changes.size() - 1) return {};

		auto mem = changes[++current];
		balance = mem->balance;
		return mem;
	}

	friend ostream& operator<<(ostream& os, const BankAccountTwo& acc) {
		os << "balance: " << acc.balance;
		return os;
	}
};

int memMain() {
//	MemBankAccount ba{100};
//	auto m1 = ba.deposit(50);
//	auto m2 = ba.deposit(75);
//	cout << ba << endl;
//	ba.restore(m1);
//	cout << ba << endl;

	BankAccountTwo ba{100};
	ba.deposit(50);
	ba.deposit(25);
	cout << ba << endl;

	ba.undo();
	cout << ba << endl;
	ba.undo();
	cout << ba << endl;
	ba.redo();
	cout << ba << endl;

	return 0;
}
