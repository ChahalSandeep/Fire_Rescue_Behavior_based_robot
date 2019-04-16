/*
 * Behavior.h
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear(Sandeep, Cem, Michael, Shreesha)
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

class Behavior {
protected:

	bool triggered;
public:
	Behavior();
	static int sonar_angle, hit_count ;
	virtual bool isTriggered();
	virtual bool act() ;
	virtual void reset();
	virtual void initialize();
	virtual ~Behavior();

};

#endif /* BEHAVIOR_H_ */
