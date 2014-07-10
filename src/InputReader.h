/*
 * InputReader.h
 *
 *
 *      Author: pedro
 */


#ifndef INPUTREADER_H_
#define INPUTREADER_H_
#include <string>
#include <iostream>
#include <fstream>
#include "Graph.h"
using namespace std;

class InputReader {

	ifstream myfile;

public:
	InputReader();
	virtual ~InputReader();
	int loadFile(Graph *G);
	char getAlphanum();
};




#endif /* INPUTREADER_H_ */
