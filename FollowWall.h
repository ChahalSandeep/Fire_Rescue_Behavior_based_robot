/*
 * FollowWall.h
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear(Sandeep, Cem, Michael, Shreesha)
 */

#ifndef FOLLOWWALL_H_
#define FOLLOWWALL_H_

#include "Behavior.h"

class FollowWall: public Behavior {

public:
	FollowWall();
	void reintialize();
	bool isTriggered();
	bool act();
	void reset();
	void initialize();
	void initialize(int sonar_angle);
	virtual ~FollowWall();
};

#endif /* FOLLOWWALL_H_ */
