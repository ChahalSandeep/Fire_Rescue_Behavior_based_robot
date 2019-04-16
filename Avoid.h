/*
 * Avoid.h
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear(Sandeep, Cem, Michael, Shreesha)
 */

#ifndef AVOID_H_
#define AVOID_H_

#include "Behavior.h"

class Avoid: public Behavior {
public:
	Avoid();
	bool isTriggered();
	bool act();
	void initialize();
	void reset();
	virtual ~Avoid();
};

#endif /* AVOID_H_ */
