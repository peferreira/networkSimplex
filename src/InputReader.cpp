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



int InputReader::loadFile(){
	string line;
	if(myfile.is_open()){
		char c = myfile.get();

		while( myfile.good()){
    		if(isalnum(c)){
    		cout << c;
    		}
    		c = myfile.get();

    	}
    	myfile.close();
    	return 1;
    }
    else cout << "Unable to openfile";
    return 0;
}
