/*
 * Pimpl.cpp
 *
 *  Created on: Apr 24, 2024
 *      Author: necar
 */

#include "Pimpl.hpp"

template <typename T>
Pimpl<T>::Pimpl(): impl{new T{}} {}

template <typename T>
template <typename ...Args>
Pimpl<T>::Pimpl(Args&& ...args): impl{new T{std::forward<Args>(args)...}} {}

template <typename T>
T* Pimpl<T>::operator->() {
	return impl.get();
}

template <typename T>
T& Pimpl<T>::operator*() {
	return *impl.get();
}
