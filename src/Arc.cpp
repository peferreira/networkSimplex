/*
 * Arc.cpp
 *
 *  Created on: Jul 5, 2014
 *      Author: pedro
 */

#include "Arc.h"

Arc::Arc(bool fake, int v, int w, int value) {
	this->fake = fake;
	this->v = v;
	this->w = w;
	this->value = value;
}

Arc::~Arc() {
	// TODO Auto-generated destructor stub
}

