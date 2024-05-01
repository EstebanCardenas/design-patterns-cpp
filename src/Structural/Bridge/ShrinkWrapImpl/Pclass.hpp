/*
 * Pclass.hpp
 *
 *  Created on: Apr 24, 2024
 *      Author: necar
 */

#pragma once

#include "Pimpl.hpp"

class Impl;

class Pclass {
	Pimpl<Impl> impl;
};
