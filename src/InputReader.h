/*
 * InputReader.h
 *
 *  Created on: Jul 3, 2014
 *      Author: pedro
 */


#ifndef INPUTREADER_H_
#define INPUTREADER_H_
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class InputReader {

	ifstream myfile;

public:
	InputReader();
	virtual ~InputReader();
	int loadFile();
};




#endif /* INPUTREADER_H_ */
