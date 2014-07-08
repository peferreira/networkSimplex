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

Graph SimplexForNetworks::Initialization(Graph G) {
	int i;
	int initVertex = G.getInitialVertex();
	int finishVertex = G.getFinishVertex();
	int *new_x_array = new int[G.getNumV()];
	for (i = 0; i < G.getNumV(); i++) {
		if (i == finishVertex) {
			new_x_array[i] = -1 * G.getProdEscoado();
		} else {
			new_x_array[i] = 0;
		}
	}

	G.setXArray(new_x_array);

	return G;
	/*clone.printMatrixADJ();
	 clone.printArcDetails();*/
}

/*void SimplexForNetworks::NetworkSimplex(Graph G) {

 }*/
void initializeAuxiliarArrays(Graph G) {

}
Graph SimplexForNetworks::addArtificialArcs(Graph G) {
	int i;
	int initVertex = G.getInitialVertex();
	int finishVertex = G.getFinishVertex();
	int *parent = G.getParent();

	Graph clone = G.clone();
	int *new_parent = new int[G.getNumV()];
	int *new_altura = new int[G.getNumV()];
	int *new_x_array = new int[G.getNumV()];
	int *new_y_array = new int[G.getNumV()];
	new_altura[initVertex] = 0;
	for (i = 0; i < G.getNumV(); i++) {
		new_y_array[i] = 0;
		new_x_array[i] = 0;
		if (parent[i] != initVertex) {
			if (i == finishVertex) {
				if (!(G.existArc2(initVertex, i))) {
					clone.insertArtificialArc(false, initVertex, i,
							clone.getProdEscoado(), 1);
					new_y_array[i] = 1;
					//cout << " y:" << new_y_array[i] << " i:" << i << '\n';

				}
				new_x_array[i] = -1 * clone.getProdEscoado();

			} else {
				if (!(G.existArc2(initVertex, i))) {
					new_y_array[i] = 1;
					clone.insertArtificialArc(false, initVertex, i, 0, 1);
				}

				new_x_array[i] = 0;
			}

		}
		new_parent[i] = initVertex;
		if (i != initVertex) {
			new_altura[i] = new_altura[initVertex] + 1;
		}
	}

	clone.setParent(new_parent);
	clone.setAltura(new_altura);
	clone.setXArray(new_x_array);
	clone.setYArray(new_y_array);
	return clone;
	/*clone.printMatrixADJ();
	 clone.printArcDetails();*/
}

Arc SimplexForNetworks::findEnteringArc(Graph tree, Graph T) {
	int *y = tree.getYArray();
	Arc *a = NULL;
	int i;
	list<Arc>::iterator it;
	for (i = 0; i < T.getNumV(); i++) {
		for (it = T.getBegin(i); it != T.getEnd(i); it++) {
			if (!(it->isArtificial()) && !(it->isFake())) {
				if ((y[i] + it->getCusto()) < y[it->getW()]) {
					cout << "v:" << it->getV() << " w:" << it->getW() << '|';
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
	int verticeLimitador = v;
	int h1, h2, temp, x, y;
	int *xArray = T.getXArray();
	h1 = T.getAltura(v);
	h2 = T.getAltura(w);
	x = w;
	y = v;

	while (h1 > h2) {
		if (xArray[x] < 0) {
			if (-1 * xArray[x] <= limitator) {
				limitator = -1 * xArray[x];
				verticeLimitador = x;
			}
		}
		x = parent[x];
		h1 = T.getAltura(x);
	}
	while (h2 > h1) {
		if (xArray[y] > 0) {
			if (xArray[x] <= limitator) {
				limitator = xArray[x];
				verticeLimitador = y;

			}
		}
		y = parent[y];
		h2 = T.getAltura(y);
	}
	while (x != y) {
		if (xArray[x] < 0) {
			if (-1 * xArray[x] <= limitator) {
				limitator = -1 * xArray[x];
				verticeLimitador = x;

			}
		}
		x = parent[x];
		if (xArray[y] > 0) {
			if (xArray[x] <= limitator) {
				limitator = xArray[x];
				verticeLimitador = y;

			}
		}
		y = parent[y];
	}
	T.removeArc(verticeLimitador,parent[verticeLimitador]);
	T.insertArc(false,v,w,0);
	return limitator;
}

/*
 int SimplexForNetworks::findCycle(int v, int w, Graph T) {
 int *parent = T.getParent();
 int limitator = T.getProdEscoado();
 list<int> A;
 list<int> B;
 list<int>::iterator it;

 int h1, h2, temp, x, y;
 h1 = T.getAltura(v);
 h2 = T.getAltura(w);
 if (h1 >= h2) {
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
 int i;

 updateXArray(A, B, v, w, T, limitator);
 /*A.push_back(x);
 A.splice(A.end(),B);
 for(it = A.begin(); it != A.end(); it++){
 cout << *it << " ";
 }*/
/*	return limitator;
 }*/

int modulo(int a) {
	if (a > 0) {
		return a;
	} else
		return -1 * a;
}
void SimplexForNetworks::updateXArray(list<int> A, list<int> B, int v, int w,
		Graph T, int limitator) {
	int *xArray = T.getXArray();
//cout << limitator << "AQUIIII";
	list<int>::iterator it;
	if (v == *A.begin()) {
		for (it = A.begin(); it != A.end(); it++) {
			if (*it != w) {
				xArray[*it] = xArray[*it] + (-1) * limitator;
			}
		}
		for (it = B.begin(); it != B.end(); it++) {
			if (*it != w)
				xArray[*it] = xArray[*it] + limitator;
		}
	} else {
		for (it = B.begin(); it != B.end(); it++) {
			if (*it != w)
				xArray[*it] = xArray[*it] + (-1) * limitator;
		}
		for (it = A.begin(); it != A.end(); it++) {
			if (*it != w)
				xArray[*it] = xArray[*it] + limitator;
		}
	}

}

void SimplexForNetworks::printListInt(list<int> L) {
	list<int>::iterator it;
	for (it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << '\n';
}

int findLimitatorInPath(int *xArray, list<int> L, int limitador, int sinal,
		int *Lim) {
	list<int>::iterator it;
	for (it = L.begin(); it != L.end(); it++) {
		if (sinal * xArray[*it] > 0) {
			if ((sinal * xArray[*it]) <= limitador) {
				limitador = sinal * xArray[*it];
				*Lim = *it;
			}
		}
	}
	return limitador;
}

int SimplexForNetworks::findLimitator(list<int> A, list<int> B, int v, int w,
		Graph T) {
	int *xArray = T.getXArray();
	list<int>::iterator it;
	int z = -1;
	int limitador = T.getProdEscoado();
	int indice_limitador;
	int vLim;
	if (v == *A.begin()) {
		limitador = findLimitatorInPath(xArray, A, limitador, 1, &vLim);
		limitador = findLimitatorInPath(xArray, B, limitador, -1, &vLim);
	} else {
		limitador = findLimitatorInPath(xArray, B, limitador, 1, &vLim);
		limitador = findLimitatorInPath(xArray, A, limitador, -1, &vLim);
	}
	T.removeArc(vLim, T.getParent()[vLim]);
	return limitador;

}

/*void SimplexForNetworks::NetworkSimplex(Graph G) {
 Graph T = addArtificialArcs(G);
 Arc entering_arc = findEnteringArc(T);
 int limitator;
 limitator = findCycle(entering_arc.getV(), entering_arc.getW(), T);

 }*/
