/*
 * Graph.h
 *
 *  Created on: Jul 3, 2014
 *      Author: pedro
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <list>
#include "Arc.h"
using namespace std;
class Graph {
private:
	int h;
	int conta;
	int *pre;
	int *parent;
	int *altura;
	int numV;
	int numA;
	list<Arc> *matrixADJ;
	void dfsR(int);
	void removeA(int,int);
	void insertA(bool,int,int,int);

public:
	Graph();
	virtual ~Graph();
	void insertArc(bool,int,int,int);
	void removeArc(int,int);
	void printMatrixADJ();
	list<Arc>::iterator existArc(int,int);
	int numArc(){return numA;}
	void graphDFS();
	void init(int numV);
	int *getParent(){return parent;}
	int getAltura(int i){return altura[i];}
	list<Arc>::iterator getEnd(int x){return matrixADJ[x].end();};
	int getNumV(){return numV;}


};

#endif /* GRAPH_H_ */
