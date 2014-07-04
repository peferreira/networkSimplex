/*
 * Graph.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: pedro
 */

#include "Graph.h"
#include <iostream>
Graph::Graph(int V) {
	numV = V;
	numA = 0;
	matrixADJ = new list<int> [V];
	pre = new int[V];
}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

void Graph::insertA(int x, int y) {
	if (!existArc(x, y)) {
		matrixADJ[x].push_back(y);
		(this->numA)++;
	}
}

void Graph::removeA(int x, int y) {
	if (existArc(x, y)) {
		matrixADJ[x].remove(y);
		(this->numA)--;
	}
}

bool Graph::existArc(int x, int y) {
	list<int>::iterator it = matrixADJ[x].begin();
	while (it != matrixADJ[x].end()) {
		if (*it == y) {
			return true;
		};
		it++;
	}
	return false;
}

void Graph::printMatrixADJ() {
	for (int i = 0; i < numV; i++) {
		cout << i << ':';
		list<int>::iterator it = matrixADJ[i].begin();
		while (it != matrixADJ[i].end()) {
			cout << *it << " ";
			it++;
		}
		cout << '\n';
	}
}

void Graph::dfsR(int v) {
	list<int>::iterator a;
	pre[v] = conta++;
	for (a = matrixADJ[v].begin(); a != matrixADJ[v].end(); a++){
		if (pre[*a] == -1)
			dfsR(*a);
	}
}

void Graph::graphDFS() {
	int v;
	conta = 0;
	for (v = 0; v < numV; v++)
		pre[v] = -1;
	for (v = 0; v < numV; v++)
		if (pre[v] == -1)
			dfsR(v);
}

