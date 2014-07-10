/*
 * Graph.cpp
 *
 *
 *      Author: pedro
 */

#include "Graph.h"
#include <iostream>
Graph::Graph() {
	ini = end = produtoEscoado = h = conta = numV = numA = 0;
	pre = altura = parent = x = y = d = cycle = NULL;
	matrixADJ = NULL;
}

Graph::~Graph() {

}

void Graph::init(int V, int ini, int end, int produtoEscoado) {
	int i;
	this->ini = ini;
	this->end = end;
	this->produtoEscoado = produtoEscoado;
	conta = 0;
	numV = V;
	matrixADJ = new list<Arc> [V];
	pre = new int[V];
	parent = new int[V];
	altura = new int[V];
	y = new int[V];
	x = new int[V];
	d = new int[V];
	cycle = new int[V];

	for (i = 0; i < V; i++) {
		d[i] = x[i] = y[i] = parent[i] = altura[i] = pre[i] = 0;
		cycle[i] = -1;
	}
}

void Graph::insertA(bool fake, int x, int y, int custo_aresta, int valueX,
		bool artificial) {
	Arc *new_arc;
	list<Arc>::iterator it = existArc(x, y);
	if (it == matrixADJ[x].end()) {
		new_arc = new Arc(fake, x, y, custo_aresta, valueX, artificial);
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
void Graph::removeArc(int x, int y) {
	removeA(x, y);
	removeA(y, x);
}
void Graph::insertArc(bool fake, int x, int y, int value) {
	insertA(fake, x, y, value, 0, false);
	insertA(!fake, y, x, value, 0, false);
}
void Graph::insertArtificialArc(bool fake, int x, int y, int valueX,
		int custo_aresta) {
	insertA(fake, x, y, custo_aresta, valueX, true);
	insertA(!fake, y, x, custo_aresta, valueX, true);
}

list<Arc>::iterator Graph::existArc(int v, int w) {
	int numV;
	list<Arc>::iterator it = matrixADJ[v].begin();
	numV = getNumV();

	if (v > numV || w > numV) {
		cout << "vertice acessado é inexistente";
	}
	while (it != matrixADJ[v].end()) {
		if (it->getW() == w) {
			return it;
		};
		it++;
	}
	return it;
}

bool Graph::existArc2(int v, int w) {
	int numV;
	list<Arc>::iterator it = matrixADJ[v].begin();
	numV = getNumV();

	if (v > numV || w > numV) {
		cout << "vertice acessado é inexistente";
	}
	while (it != matrixADJ[v].end()) {
		if (it->getW() == w) {
			return true;
		};
		it++;
	}
	return false;
}

void Graph::printMatrixADJ() {
	list<Arc>::iterator it;

	for (int i = 0; i < numV; i++) {
		cout << i << ':';
		it = matrixADJ[i].begin();
		while (it != matrixADJ[i].end()) {

			cout << it->getW() << " ";
			it++;
		}
		cout << '\n';
	}
}
int Graph::getCustoArc(int v, int w) {
	int numV;
	list<Arc>::iterator it = matrixADJ[v].begin();
	numV = getNumV();
	if (v > numV || w > numV) {
		cout << "vertice acessado é inexistente";
	}
	while (it != matrixADJ[v].end()) {
		if (it->getW() == w) {
			return it->getCusto();
		};
		it++;
	}
	return -5;
}

void Graph::printArcDetails() {
	list<Arc>::iterator it;
	for (int i = 0; i < numV; i++) {
		it = matrixADJ[i].begin();
		while (it != matrixADJ[i].end()) {
			cout << "v:" << it->getV() << " w:" << it->getW() << " Arc Fake:"
					<< it->isFake() << " Arc Artificial:" << it->isArtificial()
					<< " custo Aresta:" << it->getCusto() << '\n';

			it++;
		}
	}
}



void Graph::dfsR(int v) {
	list<Arc>::iterator it;
	pre[v] = conta++;
	for (it = matrixADJ[v].begin(); it != matrixADJ[v].end(); it++) {
		if (pre[it->getW()] == -1) {
			if (it->isFake()) {
				d[it->getW()] = -1;
				y[it->getW()] = y[v] - it->getCusto();

			} else {
				d[it->getW()] = 1;
				y[it->getW()] = y[v] + it->getCusto();
			}
			parent[it->getW()] = v;
			altura[it->getW()] = altura[v] + 1;
			dfsR(it->getW());
		}
	}
}

void Graph::graphDFS(int start) {
	int v;
	conta = 0;
	for (v = 0; v < numV; v++) {
		pre[v] = -1;
		altura[v] = 0;
		parent[v] = 0;
		y[v] = 0;
		d[v] = 0;
	}
	if (start < 0) {
		v = getInitialVertex();
	} else {
		v = start;
	}

	if (pre[v] == -1) {
		parent[v] = v;
		altura[v] = 0;
		dfsR(v);
	}

}


Graph Graph::clone() {
	int i;
	int numV;
	list<Arc>::iterator it;
	Graph new_graph;
	i = 0;
	numV = getNumV();
	new_graph.init(numV, getInitialVertex(), getFinishVertex(), produtoEscoado);
	new_graph.numA = numArc();

	for (i = 0; i < numV; i++) {
		for (it = matrixADJ[i].begin(); it != matrixADJ[i].end(); it++) {
			new_graph.insertA(it->isFake(), i, it->getW(), 0, 0, false);
		}
		new_graph.parent[i] = parent[i];
		new_graph.altura[i] = altura[i];
		new_graph.pre[i] = pre[i];
	}

	return new_graph;
}

Graph Graph::montaEstruturaArvore() {
	int i;
	int numV;
	Graph new_graph;
	list<Arc>::iterator it;
	i = 0;
	numV = getNumV();
	new_graph.init(numV, getInitialVertex(), getFinishVertex(),
			getProdEscoado());

	for (i = 0; i < numV; i++) {
		for (it = matrixADJ[i].begin(); it != matrixADJ[i].end(); it++) {

			if ((it->getV() == getInitialVertex())) {
				new_graph.insertA(false, i, it->getW(), 0, it->getValueX(),
						false);
				new_graph.insertA(true, it->getW(), i, 0, it->getValueX(),
						false);
			} else if (it->getW() == getInitialVertex()) {
				new_graph.insertA(true, i, it->getW(), 0, it->getValueX(),
						false);
				new_graph.insertA(false, it->getW(), i, 0, it->getValueX(),
						false);
			}

		}
		if (i != getInitialVertex()) {
			new_graph.insertA(true, i, getInitialVertex(), 1, it->getValueX(),
					true);
			new_graph.insertA(false, getInitialVertex(), i, 1, it->getValueX(),
					true);
			if (y[i] > 0) {
				y[i] = y[getInitialVertex()] + 1;
			}

		}
	}
	return new_graph;
}

