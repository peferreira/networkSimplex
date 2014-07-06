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
	int fake;
public:
	Arc(bool, int, int, int);
	virtual ~Arc();
	int getV(){return v;}
	int getW(){return w;}
};

#endif /* ARC_H_ */
