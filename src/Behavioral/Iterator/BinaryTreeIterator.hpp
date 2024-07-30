/*
 * BinaryTreeIterator.hpp
 *
 *  Created on: Jun 18, 2024
 *      Author: necar
 */

#pragma once

#include <string>
#include <iostream>

using namespace std;

template <typename T>
struct BinaryTree;

template <typename T>
struct Node {
	T value = T();
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
	Node<T>* parent = nullptr;
	BinaryTree<T>* tree = nullptr;

	Node(T value) : value{value} {}

	Node(T value, Node<T>* l, Node<T>* r) :
		value{value}, left{l}, right{r} {
			left->tree = right->tree = tree;
			left->parent = right->parent = this;
		}

	void set_tree(BinaryTree<T>* ptr) {
		tree = ptr;
		if (left) {
			left->set_tree(ptr);
		}
		if (right) {
			right->set_tree(ptr);
		}
	}

	~Node() {
		if (left) {
			delete left;
		}
		if (right) {
			delete right;
		}
	}
};

template <typename T>
struct BinaryTree {
	Node<T>* root = nullptr;

	BinaryTree(Node<T> *r) : root{r} {
		r->set_tree(this);
	}

	~BinaryTree() {
		if (root) delete root;
	}

	template <typename U>
	struct InOrderIterator {
		Node<U>* current;

		InOrderIterator(Node<U>* c) : current{c} {}

		bool operator!=(const InOrderIterator<U>& other) {
			return current != other.current;
		}

		InOrderIterator<U>& operator++() {
			if (current->right) {
				current = current->right;
				while (current->left) {
					current = current->left;
				}
			} else {
				Node<U>* p = current->parent;
				while (p && current == p->right) {
					current = p;
					p = p->parent;
				}
				current = p;
			}
			return *this;
		}

		Node<U>& operator*() {
			return *current;
		}
	};

	typedef InOrderIterator<T> iterator;

	iterator begin() {
		Node<T>* n = root;
		if (n) {
			while (n->left) {
				n = n->left;
			}
		}
		return iterator{n};
	}

	iterator end() {
		return iterator{nullptr};
	}
};

int bTreeItMain() {
	Node<string>* root = new Node<string>{
		"me",
		new Node<string>{
			"mom",
			new Node<string>{
				"mom's mom"
			},
			new Node<string>{
				"mom's dad"
			}
		},
		new Node<string>{
			"dad"
		}
	};
	BinaryTree<string>* tree = new BinaryTree<string>{root};
	auto it = tree->begin();
	while (it != tree->end()) {
		string name = (*it).value;
		cout << name << endl;
		++it;
	}
	return 0;
}
