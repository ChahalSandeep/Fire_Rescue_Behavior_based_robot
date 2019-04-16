/*
 * Explore.h
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear
 */

#ifndef EXPLORE_H_
#define EXPLORE_H_

#include "Behavior.h"

class Explore: public Behavior {
public:
	Explore();
	bool isTriggered();
	bool act();
	void reset();
	void initialize();
	virtual ~Explore();
};

#endif /* EXPLORE_H_ */
