/*
 * SimplexForNetworks.cpp
 *
 *  Created on: Jul 6, 2014
 *      Author: pedro
 */
#include <iostream>
#include "SimplexForNetworks.h"
#include <list>
SimplexForNetworks::SimplexForNetworks() {
	// TODO Auto-generated constructor stub

}

SimplexForNetworks::~SimplexForNetworks() {
	// TODO Auto-generated destructor stub
}

void SimplexForNetworks::Initialization(Graph G) {

}

void SimplexForNetworks::NetworkSimplex(Graph G) {

}

Graph SimplexForNetworks::addArtificialArcs(Graph G) {
	int i;
	int initVertex = G.getInitialVertex();
	int finishVertex = G.getFinishVertex();
	int *parent = G.getParent();
	Graph clone = G.clone();
	int *new_parent = new int[G.getNumV()];
	int *new_altura = new int[G.getNumV()];

	for (i = 0; i < G.getNumV(); i++) {
		if (parent[i] != initVertex) {
			if (i == finishVertex) {
				clone.insertArtificialArc(false, initVertex, i,
						clone.getProdEscoado());
			} else {
				clone.insertArtificialArc(false, initVertex, i, 0);
			}

		}
		new_parent[i] = initVertex;
		if (i != initVertex) {
			new_altura[i] = G.getAltura(initVertex) + 1;
		} else
			new_altura[i] = G.getAltura(i);
	}
	clone.setParent(new_parent);
	clone.setAltura(new_altura);

	return clone;
	/*clone.printMatrixADJ();
	 clone.printArcDetails();*/
}

Arc SimplexForNetworks::findEnteringArc(Graph T){
	int *y = T.getYArray();
	Arc *a = NULL;
	int i;
	list<Arc>::iterator it;
	for(i = 0; i < T.getNumV();i++){
		for(it = T.getBegin(i); it != T.getEnd(i); it++){
			if(!(it->isArtificial()) && !(it->isFake())){
				if((y[i] + it->getValue()) < y[it->getW()]){
					return *it;
					//cout << "v:" << it->getV() << " w:" << it->getW() << '|';

				}
			}
		}
	}
	return *a;
}


/*supoe x > y, h1 > h2*/
int SimplexForNetworks::findCycle(int v, int w, Graph T) {
	int *parent = T.getParent();
	int limitator = T.getProdEscoado();
	list<int> A;
	list<int> B;
	list<int>::iterator it;

	int h1, h2, temp, x, y;
	h1 = T.getAltura(v);
	h2 = T.getAltura(w);
	if (h1 > h2) {
		x = v;
		y = w;
	} else {
		temp = h1;
		h1 = h2;
		h2 = temp;
		x = w;
		y = v;
	}
	while (h1 != h2) {
		A.push_back(x);
		x = parent[x];
		h1 = T.getAltura(x);

	}
	while (x != y) {
		A.push_back(x);
		B.push_front(y);
		x = parent[x];
		y = parent[y];
	}
	limitator = findLimitator(A, B, v, w, T);

	/*A.push_back(x);
	 A.splice(A.end(),B);
	 for(it = A.begin(); it != A.end(); it++){
	 cout << *it << " ";
	 }*/
	return limitator;
}

int SimplexForNetworks::findLimitator(list<int> A, list<int> B, int v, int w,
		Graph T) {
	int *xArray = T.getXArray();
	list<int>::iterator it;
	int z = -1;
	int limitador = T.getProdEscoado();
	if (v == *A.begin()) {
		for (it = A.begin(); it != A.end(); it++) {
			if (xArray[*it] >= 0) {
				if ((xArray[*it]) < limitador) {
					limitador = xArray[*it];
					z = *it;
				}
			}
		}
		for (it = B.begin(); it != B.end(); it++) {
			if (xArray[*it] <= 0) {
				if ((-1 * xArray[*it]) < limitador) {
					limitador = -1 * xArray[*it];
					z = *it;

				}
			}
		}
	} else {
		for (it = B.begin(); it != B.end(); it++) {
			if (xArray[*it] >= 0) {
				if ((xArray[*it]) < limitador) {
					limitador = xArray[*it];
					z = *it;

				}
			}
		}
		for (it = A.begin(); it != A.end(); it++) {
			if (xArray[*it] <= 0) {
				if ((-1 * xArray[*it]) < limitador) {
					limitador = -1 * xArray[*it];
					z = *it;

				}
			}
		}
	}
	//cout << z << '\n';
	return limitador;

}
