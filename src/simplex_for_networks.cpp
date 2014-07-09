#include "Graph.h"
#include "InputReader.h"
#include "SimplexForNetworks.h"

void printVector2(int *t, int size, string s) {
	cout << s << '\n';
	int i;
	cout << "[ ";
	for (i = 0; i < size; i++) {
		cout << t[i] << " ";
	}
	cout << "]" << '\n';
}

void printAuxArrays(Graph T) {
	int *t = T.getXArray();
	printVector2(t, T.getNumV(), "X");
	t = T.getParent();
	printVector2(t, T.getNumV(), "Parent");
	t = T.getYArray();
	printVector2(t, T.getNumV(), "Y");
	t = T.getPre();
	printVector2(t, T.getNumV(), "PRE");
	t = T.getDArray();
	printVector2(t, T.getNumV(), "Direcao");
	//T.printMatrixADJ();
	//T.printArcDetails();
}
int main() {
	InputReader input;
	SimplexForNetworks simplex;

	int i;
	int V;
	int *t, *h;
	Graph *G;
	G = new Graph();
	input.loadFile(G);

	Graph T = G->montaEstruturaArvore();
	Graph H = G->clone();

	T = simplex.Initialization(T);
	printAuxArrays(T);

	T.graphDFS();

	printAuxArrays(T);

	Arc c = simplex.findEnteringArc(T, H);
	while (c.getV() >= 0) {
		simplex.findCycle(c.getV(), c.getW(), &T, c.isFake());
		printAuxArrays(T);

		T.graphDFS();
		c = simplex.findEnteringArc(T, H);
	}

	cout << "FIMMM DA PRIMEIRA FASE!!!!!!!!!!!!!!!!!!!" << '\n';

	cout << '\n';
	T = simplex.InicializacaoFase2(*G, T);

	T.graphDFS();

	c = simplex.findEnteringArc(T, *G);
	while (c.getV() >= 0) {
		simplex.findCycle(c.getV(), c.getW(), &T, c.isFake());

		T.graphDFS();
		c = simplex.findEnteringArc(T, *G);

	}


}
