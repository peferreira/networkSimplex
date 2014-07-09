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
	Graph Initialization(Graph G);
	Graph InicializacaoFase2(Graph G, Graph T);
	Graph addArtificialArcs(Graph G);
	int findCycle(int v, int w, Graph T);
	Arc findEnteringArc(Graph T, Graph tree);
	void updateXArray(list<int> A, list<int> B, int v, int w,Graph T,int limitator);
	void printListInt(list<int> L);
};

#endif /* SIMPLEXFORNETWORKS_H_ */
