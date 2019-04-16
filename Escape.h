/*
 * Escape.h
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear
 */

#ifndef ESCAPE_H_
#define ESCAPE_H_

#include "Behavior.h"

class Escape: public Behavior {
public:
	Escape();
	bool isTriggered();
	bool act();
	void reset();
	void initialize();
	virtual ~Escape();
};

#endif /* ESCAPE_H_ */
