/*
 * Arc.cpp
 *
 *  Created on: Jul 5, 2014
 *      Author: pedro
 */

#include "Arc.h"

Arc::Arc(bool fake, int v, int w, int custo) {
	this->fake = fake;
	this->v = v;
	this->w = w;
	this->valueX = 0 ;
	this->custo_aresta = custo;
	artificial = false;
}

Arc::Arc(bool fake, int v, int w, int custo,int valueX, bool artificial) {
	this->fake = fake;
	this->v = v;
	this->w = w;
	this->valueX = valueX;
	this->custo_aresta = custo;
	this->artificial = artificial;
}

Arc::~Arc() {
	// TODO Auto-generated destructor stub
}

