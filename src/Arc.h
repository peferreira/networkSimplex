/*
 * Arc.h
 *
 *  Created on: Jul 5, 2014
 *      Author: pedro
 */

#ifndef ARC_H_
#define ARC_H_

class Arc {
private:
	int value;
	int v, w;
	bool fake;
	bool artificial;
public:
	Arc(bool, int, int, int);
	Arc(bool, int, int, int, bool);

	virtual ~Arc();
	int getV(){return v;}
	int getW(){return w;}
	bool isArtificial(){return artificial;}
	bool isFake(){return fake;}
	void setArtificial(bool isArtificial){artificial = isArtificial;};
	int getValue(){return value;}
};

#endif /* ARC_H_ */
