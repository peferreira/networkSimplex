/*
 * SimplexForNetworks.cpp
 *
 *
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
/*inicializacao da fase 1 no metodo simplex para redes*/

Graph SimplexForNetworks::Initialization(Graph G) {
	int i;
	int finishVertex;
	int *new_x_array;
	new_x_array = new int[G.getNumV()];
	finishVertex = G.getFinishVertex();

	for (i = 0; i < G.getNumV(); i++) {
		if (i == finishVertex) {
			new_x_array[i] = G.getProdEscoado();

		} else {
			new_x_array[i] = 0;
		}

	}
	G.setXArray(new_x_array);
	return G;
}

/*inicializacao da fase 2 no metodo simplex para redes*/
Graph SimplexForNetworks::InicializacaoFase2(Graph G, Graph T) {
	int i;
	int numV;
	list<Arc>::iterator it;
	int *xArray;
	int *new_xArray;
	Graph new_tree;
	i = 0;

	numV = T.getNumV();
	xArray = T.getXArray();
	new_xArray = new int[numV];
	new_tree.init(numV, T.getInitialVertex(), T.getFinishVertex(),
			T.getProdEscoado());

	for (i = 0; i < numV; i++) {
		for (it = T.getBegin(i); it != T.getEnd(i); it++) {
			new_tree.insertArc(it->isFake(), it->getV(), it->getW(),
					G.getCustoArc(it->getV(), it->getW()));
		}
		new_xArray[i] = xArray[i];
	}
	new_tree.setXArray(new_xArray);
	return new_tree;
}



/*funcao responsavel por encontrar um arco promissor para entrar na arvore, metodo
 * utilizado: encontra o primeiro arco promissor*/
Arc SimplexForNetworks::findEnteringArc(Graph tree, Graph T) {
	int *y;
	Arc *a;
	int i;
	list<Arc>::iterator it;
	a = new Arc(true, -1, -1, -1);
	y = tree.getYArray();
		for (i = 0; i < T.getNumV(); i++) {
		for (it = T.getBegin(i); it != T.getEnd(i); it++) {
			if (!(it->isArtificial())) {
				if ((y[i] + it->getCusto()) < y[it->getW()]) {
					return *it;
				}
			}
		}
	}
	return *a;
}

/*funcao responsavel por achar o ciclo gerado com a inclusao do vertice v-w na arvore T*/
int SimplexForNetworks::findCycle(int v, int w, Graph *T, int value) {
	int *parent;
	int limitator;
	int verticeLimitador;
	int h1, h2, x, y;
	int *xArray;
	int *d;
	bool quebrouEmA;
	list<int> A;
	list<int> B;
	list<int>::iterator it;
	verticeLimitador = v;
	parent = T->getParent();
	xArray = T->getXArray();
	d = T->getDArray();
	x = v;
	y = w;
	h1 = T->getAltura(v);
	h2 = T->getAltura(w);
	limitator = T->getProdEscoado();

	while (h1 > h2) {
		A.push_back(x);
		if (d[x] < 0) {
			if (xArray[x] <= limitator) {
				limitator = xArray[x];
				verticeLimitador = x;
				quebrouEmA = true;
			}
		}
		x = parent[x];
		h1 = T->getAltura(x);
	}
	while (h2 > h1) {
		B.push_back(y);
		if (d[y] > 0) {
			if (xArray[y] <= limitator) {
				limitator = xArray[y];
				verticeLimitador = y;
				quebrouEmA = false;
			}
		}
		y = parent[y];
		h2 = T->getAltura(y);
	}
	while (x != y) {
		A.push_back(x);
		if (d[x] < 0) {
			if (xArray[x] <= limitator) {
				limitator = xArray[x];
				verticeLimitador = x;
				quebrouEmA = true;
			}
		}
		x = parent[x];
		B.push_back(y);
		if (d[y] > 0) {
			if (xArray[y] <= limitator) {
				limitator = xArray[y];
				verticeLimitador = y;
				quebrouEmA = false;
			}
		}
		y = parent[y];

	}

	updateXArray(A, B, v, w, T, limitator, quebrouEmA, verticeLimitador);
	T->removeArc(verticeLimitador, parent[verticeLimitador]);
	T->insertArc(false, v, w, value);
	return limitator;
}

/*toda iteracao precisa corrigir os valores de X na parte da arvore que é removida
 * a aresta, pois agora cada vertice precisara ter o valor da aresta anterior a ele
 * e antes dessa iteracao ele possuia o valor da aresta que ligava ele a arvore
 * para manter a coerencia dos valores do arrayX precisamos fazer essa "correção" */

void SimplexForNetworks::corrigeX(list<int> AouB, int verticeLimitador, int *d,
		Graph *T) {
	list<int>::iterator it;
	it = AouB.begin();
	int verticeAnterior;
	int *xArray = T->getXArray();
	int temp1, temp2;
	temp1 = xArray[*it];
	while (*it != verticeLimitador) {
		verticeAnterior = *it;
		it++;
		temp2 = xArray[*it];
		xArray[*it] = temp1;
		temp1 = temp2;
	}
}

/*atualiza o array com os valores de custos nas arestas xArray*/
void SimplexForNetworks::updateXArray(list<int> A, list<int> B, int v, int w,
		Graph *T, int limitator, bool quebrouEmA, int verticeLimitador) {
	int *xArray = T->getXArray();
	int *d = T->getDArray();
	list<int>::iterator it;

	for (it = A.begin(); it != A.end(); it++) {
		if (d[*it] > 0)
			xArray[*it] = xArray[*it] + limitator;

		else
			xArray[*it] = xArray[*it] - limitator;
	}
	for (it = B.begin(); it != B.end(); it++) {
		if (d[*it] > 0) {
			xArray[*it] = xArray[*it] - limitator;
		} else {
			xArray[*it] = xArray[*it] + limitator;
		}
	}
	if (quebrouEmA) {
		corrigeX(A, verticeLimitador, d, T);
		xArray[v] = limitator;
	} else {
		corrigeX(B, verticeLimitador, d, T);
		xArray[w] = limitator;
	}
}


