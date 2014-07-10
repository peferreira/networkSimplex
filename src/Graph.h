/*
 * Graph.h
 *
 *
 *      Author: pedro
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <list>
#include "Arc.h"
using namespace std;
class Graph {
private:

	int h,conta,numV,numA,ini,end,produtoEscoado;
	int *pre ,*parent, *altura, *d, *x, *y, *cycle;
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
	int getCustoArc(int v, int w);
	int numArc(){return numA;}
	void graphDFS(int start);
	void init(int numVertices , int vInicial, int vFinal, int prodEscoado);
	int *getParent(){return parent;}
	int *getAlturaArray(){return altura;}
	int *getDArray(){return d;}
	int *getXArray(){return x;}
	int *getPre(){return pre;}
	int *getYArray(){return y;}
	void setParent(int *newParent){parent = newParent;}
	int getAltura(int i){return altura[i];}
	void setAltura(int *newAltura){altura = newAltura;}
	void setDArray(int *dArray){ d = dArray ;}
	void setXArray(int *xArray){ x = xArray ;}
	bool isArcFake(int v, int w);
	void setYArray(int *yArray){ y = yArray ;}
	int getProdEscoado(){return produtoEscoado;}
	int *getCycle(){return cycle;}
	list<Arc>::iterator getEnd(int x){return matrixADJ[x].end();};
	list<Arc>::iterator getBegin(int x){return matrixADJ[x].begin();};
	int getNumV(){return numV;}
	int getInitialVertex(){return ini;};
	int getFinishVertex(){return end;}
	Graph clone();
	void printArcDetails();
	Graph montaEstruturaArvore();
};

#endif /* GRAPH_H_ */
