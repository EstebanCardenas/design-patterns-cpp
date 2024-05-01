/*
 * Pimpl.hpp
 *
 *  Created on: Apr 24, 2024
 *      Author: necar
 */

#pragma once

#include <memory>

template <typename T>
class Pimpl {
	std::unique_ptr<T> impl;
public:
	Pimpl();
	~Pimpl();

	template <typename ...Args> Pimpl(Args&& ...args);

	T* operator->();
	T& operator*();
};
