/*
 * Graph.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: pedro
 */

#include "Graph.h"
#include <iostream>
Graph::Graph() {
	ini = 0, end = 0;
	produtoEscoado = 0;
	h = 0;
	conta = 0;
	numV = 0;
	numA = 0;
	pre = NULL;
	matrixADJ = NULL;
	altura = NULL;
	parent = NULL;
	x = NULL;
	y = NULL;
	d = NULL;
}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
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
	aux = new int[V];

	for (i = 0; i < V; i++) {
		aux[i] = d[i] = x[i] = y[i] = parent[i] = altura[i] = pre[i] = 0;
	}

}

void Graph::insertA(bool fake, int x, int y, int custo_aresta, int valueX,
		bool artificial) {
	list<Arc>::iterator it = existArc(x, y);
	Arc *new_arc;
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
	int numV = getNumV();
	if (v > numV || w > numV) {
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
bool Graph::existArc2(int v, int w) {
	int numV = getNumV();
	if (v > numV || w > numV) {
		cout << "vertice acessado é inexistente";
	}
	list<Arc>::iterator it = matrixADJ[v].begin();
	while (it != matrixADJ[v].end()) {
		if (it->getW() == w) {
			return true;
		};
		it++;
	}
	return false;
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
int Graph::getCustoArc(int v, int w) {
	int numV = getNumV();
	if (v > numV || w > numV) {
		cout << "vertice acessado é inexistente";
	}
	list<Arc>::iterator it = matrixADJ[v].begin();
	while (it != matrixADJ[v].end()) {
		if (it->getW() == w) {
			return it->getCusto();
		};
		it++;
	}
	return -5;
}

void Graph::printArcDetails() {
	for (int i = 0; i < numV; i++) {

		list<Arc>::iterator it = matrixADJ[i].begin();
		while (it != matrixADJ[i].end()) {
			cout << "v:" << it->getV() << " w:" << it->getW() << " Arc Fake:"
					<< it->isFake() << " Arc Artificial:" << it->isArtificial()
					<< " custo Aresta:"<<it->getCusto() <<'\n';

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

void Graph::graphDFS() {
	int v;
	conta = 0;
	for (v = 0; v < numV; v++) {
		pre[v] = -1;
		altura[v] = 0;
		parent[v] = 0;
		y[v] = 0;
		d[v] = 0;
	}
	for (v = getInitialVertex(); v < numV; v++) {
		if (pre[v] == -1) {
			parent[v] = v;
			altura[v] = 0;
			dfsR(v);
		}
	}

}

/*aresta fake recebe valor positivo em x, aresta nao fake recebe valor negativo*/
/*void Graph::dfsR(int v) {
 list<Arc>::iterator it;
 pre[v] = conta++;
 for (it = matrixADJ[v].begin(); it != matrixADJ[v].end(); it++) {
 if (pre[it->getW()] == -1) {
 if (it->isFake()) {
 if (ordemVertices[it->getW()] > 0) {
 //x[ordemVertices[it->getW()]] = it->getCusto();
 y[ordemVertices[it->getW()]] = y[ordemVertices[v]]
 - it->getCusto();
 } else {
 //x[it->getW()] = it->getCusto();
 y[it->getW()] = y[v] - it->getCusto();
 }
 } else {
 if (ordemVertices[it->getW()] > 0) {
 //x[ordemVertices[it->getW()]] = -1 * it->getCusto();
 y[ordemVertices[it->getW()]] = y[ordemVertices[v]]
 + it->getCusto();
 } else {
 //x[it->getW()] = -1 * it->getCusto();
 y[it->getW()] = y[v] + it->getCusto();
 }
 }
 if (ordemVertices[it->getW()] > 0) {
 parent[ordemVertices[it->getW()]] = v;
 altura[ordemVertices[it->getW()]] = altura[ordemVertices[v]]
 + 1;
 } else {
 parent[it->getW()] = v;
 altura[it->getW()] = altura[v] + 1;
 }
 dfsR(it->getW());
 }
 }
 }
 */
/*void Graph::graphDFS() {
 int v;
 conta = 0;
 for (v = 0; v < numV; v++) {
 pre[v] = -1;
 altura[v] = 0;
 parent[v] = 0;
 }
 for (v = 0; v < numV; v++)
 if (pre[v] == -1) {
 if (ordemVertices[v] > 0) {
 parent[ordemVertices[v]] = v;
 altura[ordemVertices[v]] = 0;
 } else {
 parent[v] = v;
 altura[v] = 0;
 }
 dfsR(v);
 }
 }
 */
Graph Graph::clone() {
	int i = 0;
	int numV;
	list<Arc>::iterator it;
	numV = getNumV();
	Graph new_graph;
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
	int i = 0;
	int numV;
	list<Arc>::iterator it;
	numV = getNumV();
	Graph new_graph;
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
			new_graph.insertA(true, i, getInitialVertex(), 1, it->getValueX(), true);
			new_graph.insertA(false, getInitialVertex(), i, 1, it->getValueX(), true);
			if (y[i] > 0) {
				y[i] = y[getInitialVertex()] + 1;
			}

		}
	}
	/*new_graph.printArcDetails();
	new_graph.printMatrixADJ();*/
	return new_graph;
}

