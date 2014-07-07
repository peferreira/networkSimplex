/*
 * SimplexForNetworks.h
 *
 *  Created on: Jul 6, 2014
 *      Author: pedro
 */

#ifndef SIMPLEXFORNETWORKS_H_
#define SIMPLEXFORNETWORKS_H_
#include "Graph.h"

class SimplexForNetworks {
private:
	int findLimitator(list<int> a, list<int> b, int v, int w, Graph T);

public:
	SimplexForNetworks();
	virtual ~SimplexForNetworks();
	void NetworkSimplex(Graph G);
	void Initialization(Graph G);
	Graph addArtificialArcs(Graph G);
	int findCycle(int v, int w, Graph T);
	Arc findEnteringArc(Graph T);
};

#endif /* SIMPLEXFORNETWORKS_H_ */
