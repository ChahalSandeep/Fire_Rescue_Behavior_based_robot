/*
 * FindGoal.h
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear(Sandeep, Cem, Michael, Shreesha)
 */

#ifndef FINDGOAL_H_
#define FINDGOAL_H_

#include "Behavior.h"

class FindGoal: public Behavior {
private:
	bool goalFound;
public:
	FindGoal();
	bool isTriggered();
	bool act();
	void reset();
	void initialize();
	virtual ~FindGoal();
};

#endif /* FINDGOAL_H_ */
