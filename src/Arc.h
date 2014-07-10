/*
 * Arc.h
 *
 *
 *      Author: pedro
 */

#ifndef ARC_H_
#define ARC_H_

class Arc {
private:
	int custo_aresta;
	int valueX;
	int v, w;
	bool fake;
	bool artificial;
public:
	Arc(bool fake, int v, int w,  	int custo_aresta);
	Arc(bool fake, int v, int w, int custo_aresta, int valueX ,bool artificial);
	virtual ~Arc();
	int getV(){return v;}
	int getW(){return w;}
	bool isArtificial(){return artificial;}
	bool isFake(){return fake;}
	void setArtificial(bool isArtificial){artificial = isArtificial;};
	/*int getValue(){return value;}*/
	int getCusto(){return custo_aresta;}
	int getValueX(){return valueX;}
	void setValueX(int valueX){this->valueX = valueX;}
};

#endif /* ARC_H_ */
