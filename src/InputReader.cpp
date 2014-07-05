/*
 * InputReader.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: pedro
 */

#include "InputReader.h"

InputReader::InputReader() {
	// TODO Auto-generated constructor stub
	myfile.open("test/problema.dat");
}

InputReader::~InputReader() {
	// TODO Auto-generated destructor stub

}

char InputReader::getAlphanum(){
	char c, value;
	if (myfile.is_open()) {
		while (myfile.good()) {
			c = myfile.get();

			if (isalnum(c)) {
				value = c;
				return value;
			}
		}
	}
	return '\0';
}

int InputReader::loadFile(Graph *G) {

	string line;
	if(myfile.is_open()) {
		int V,quantProd, vIni,vFim,x,y,c;
		myfile>>V;
		myfile>>vIni;
		myfile>>vFim;
		myfile>>quantProd;
		cout << V << '\n';
		cout << vIni << '\n';
		cout << vFim << '\n';
		cout << quantProd << '\n';
		G->init(V);
		while(myfile.good()) {
			myfile>>x;
			myfile>>y;
			myfile>>c;
			cout << x << ' ' << y  << ' ' << c << '\n';
			G->insertA(x,y);
		}
		myfile.close();
		return 1;
	}
	else cout << "Unable to openfile";
	return 0;
}
