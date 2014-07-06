/*
 * SimplexForNetworks.cpp
 *
 *  Created on: Jul 6, 2014
 *      Author: pedro
 */

#include "SimplexForNetworks.h"

SimplexForNetworks::SimplexForNetworks() {
	// TODO Auto-generated constructor stub

}

SimplexForNetworks::~SimplexForNetworks() {
	// TODO Auto-generated destructor stub
}

void SimplexForNetworks::Initialization(Graph G){



}

void SimplexForNetworks::NetworkSimplex(Graph G){

}

Graph SimplexForNetworks::addArtificialArcs(Graph G){
	int i;
	int initVertex = G.getInitialVertex();
	int finishVertex = G.getFinishVertex();
	int *parent = G.getParent();
	Graph clone = G.clone();
	int *new_parent = new int [G.getNumV()];
	int *new_altura = new int [G.getNumV()];

	for(i = 0; i < G.getNumV(); i++){
		if(parent[i] != initVertex){
			if(i == finishVertex){
				clone.insertArtificialArc(false, initVertex, i, clone.getProdEscoado());
			}
			else{
				clone.insertArtificialArc(false, initVertex, i, 0);
			}

		}
		new_parent[i] = initVertex;
		if(i != initVertex){
			new_altura[i] = G.getAltura(initVertex)+1;
		}
		else
			new_altura[i] = G.getAltura(i);
	}
	clone.setParent(new_parent);
	clone.setAltura(new_altura);

	return clone;
	/*clone.printMatrixADJ();
	clone.printArcDetails();*/
}

