/*
 * InputReader.cpp
 *
 *
 *      Author: pedro
 */

#include "InputReader.h"

InputReader::InputReader() {

	myfile.open("src/problema.dat");
}

InputReader::~InputReader() {

}
/*funcao de leitura do input pegando somente numeros da forma padronizada
 * pelo enunciado*/
char InputReader::getAlphanum(){
	char c, value;
	if (myfile.is_open()) {
		while (myfile.good()) {
			c = myfile.get();

			if (isdigit(c)) {
				value = c;
				return value;
			}
		}
	}
	return '\0';
}

/*abre para leitura e le do arquivo problema.dat, caminho
 * definido estaticamente no construtor*/
int InputReader::loadFile(Graph *G) {

	string line;
	if(myfile.is_open()) {
		int V,quantProdEscoado, vIni,vFim,x,y,c;
		myfile>>V;
		myfile>>vIni;
		myfile>>vFim;
		myfile>>quantProdEscoado;
		G->init(V,vIni,vFim,quantProdEscoado);
		while(myfile.good()) {
			myfile>>x;
			myfile>>y;
			myfile>>c;
			G->insertArc(false,x,y,c);

		}
		myfile.close();
		return 1;
	}
	else cout << "Unable to openfile";
	return 0;
}
