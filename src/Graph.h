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
	int *x;
	int *y;
	int numV;
	int numA;
	int ini, end;
	int produtoEscoado;
	list<Arc> *matrixADJ;
	void dfsR(int);
	void removeA(int,int);
	void insertA(bool,int,int,int,int,bool);

public:
	Graph();
	virtual ~Graph();
	void insertArc(bool,int,int,int);
	void insertArtificialArc(bool,int,int,int,int);
	void removeArc(int,int);
	void printMatrixADJ();
	list<Arc>::iterator existArc(int,int);
	bool existArc2(int,int);

	int numArc(){return numA;}
	void graphDFS();
	void init(int numVertices , int vInicial, int vFinal, int prodEscoado);
	int *getParent(){return parent;}
	int *getAlturaArray(){return altura;}
	int *getXArray(){return x;}
	int *getPre(){return pre;}
	int *getYArray(){return y;}
	void setParent(int *newParent){parent = newParent;}
	int getAltura(int i){return altura[i];}
	void setAltura(int *newAltura){altura = newAltura;}
	void setXArray(int *xArray){ x = xArray ;}

	void setYArray(int *yArray){ y = yArray ;}


	list<Arc>::iterator getEnd(int x){return matrixADJ[x].end();};
	list<Arc>::iterator getBegin(int x){return matrixADJ[x].begin();};

	int getNumV(){return numV;}
	int getInitialVertex(){return ini;};
	int getFinishVertex(){return end;}
	Graph clone();
	int getProdEscoado(){return produtoEscoado;};
	void printArcDetails();
	Graph montaEstruturaArvore();
};

#endif /* GRAPH_H_ */
