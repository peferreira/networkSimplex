/*
 * Graph.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: pedro
 */

#include "Graph.h"
#include <iostream>
Graph::Graph() {
	h = 0;
	conta = 0;
	numV = 0;
	numA = 0;
	pre = NULL;
	matrixADJ = NULL;
	altura = NULL;
	parent = NULL;
}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

void Graph::init(int V) {
	conta = 0;
	numV = V;
	matrixADJ = new list<Arc> [V];
	pre = new int[V];
	parent = new int[V];
	altura = new int[V];

}

void Graph::insertA(bool fake, int x, int y, int value) {
	list<Arc>::iterator it = existArc(x, y);
	Arc *new_arc;
	if (it == matrixADJ[x].end()) {
		new_arc = new Arc(fake, x, y, value);
		matrixADJ[x].push_back(*new_arc);
		(this->numA)++;
	}
}

void Graph::removeA(int x, int y) {
	list<Arc>::iterator it = matrixADJ[x].begin();
	it = existArc(x, y);
	if (it != matrixADJ[x].end()) {
		matrixADJ[x].erase(it);
		(this->numA)--;
	}
}
void Graph::removeArc(int x, int y){
	removeA(x,y);
	removeA(y,x);
}
void Graph::insertArc(bool fake,int x, int y,int value){
	insertA(fake,x,y,value);
	insertA(!fake,y,x,value);
}

list<Arc>::iterator Graph::existArc(int v, int w) {
	int numV = getNumV();
	if(v > numV  || w > numV){
		cout << "vertice acessado é inexistente";
	}
	list<Arc>::iterator it = matrixADJ[v].begin();
	while (it != matrixADJ[v].end()) {
		if (it->getW() == w) {
			return it;
		};
		it++;
	}
	return it;
}

void Graph::printMatrixADJ() {
	for (int i = 0; i < numV; i++) {
		cout << i << ':';
		list<Arc>::iterator it = matrixADJ[i].begin();
		while (it != matrixADJ[i].end()) {

			cout << it->getW() << " ";
			it++;
		}
		cout << '\n';
	}
}

void Graph::dfsR(int v) {
	list<Arc>::iterator it;
	pre[v] = conta++;
	for (it = matrixADJ[v].begin(); it != matrixADJ[v].end(); it++) {
		if (pre[it->getW()] == -1) {
			parent[it->getW()] = v;
			altura[it->getW()] = altura[v] + 1;
			dfsR(it->getW());
		}
	}
}

void Graph::graphDFS() {
	int v;
	conta = 0;
	for (v = 0; v < numV; v++)
		pre[v] = -1;
	for (v = 0; v < numV; v++)
		if (pre[v] == -1) {
			parent[v] = v;
			altura[v] = 0;
			dfsR(v);
		}
}

