/*
 * Graph.h
 *
 *  Created on: Jul 3, 2014
 *      Author: pedro
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <list>
using namespace std;
class Graph {
private:
	int conta;
	int *pre;
	int numV;
	int numA;
	list<int> *matrixADJ;
	void dfsR(int);

public:
	Graph();
	virtual ~Graph();
	void insertA(int,int);
	void removeA(int,int);
	void printMatrixADJ();
	bool existArc(int,int);
	int numArc(){return numA;}
	void graphDFS();
	void init(int numV);
};

#endif /* GRAPH_H_ */
