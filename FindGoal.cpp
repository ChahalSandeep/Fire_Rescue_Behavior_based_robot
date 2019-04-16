/*
 * FindGoal.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear
 */
#include <ev3.h>
#include<ctime>
#include "FindGoal.h"

#define R 0.0275
#define d 0.06


time_t str, fnsh;

/*
 * Constructor
 */
FindGoal::FindGoal() {}

/*
 * Implement virtual method from Behavior base
 * class
 */
bool FindGoal::isTriggered()
{
	// start listening to sensor
	// if goal is detected
	// trigger action

	if(readSensor(IN_2) == 5) {
			return true;
		}

	return false;
}


/*
 * Implement virtual method from Behavior base
 * class
 * This is the action the robot will take when in
 * this behavior
 */
bool FindGoal::act()
{

	Off(OUT_ABCD);

	SetLedPattern(LED_RED_FLASH);
	SetLedWarning(1);
	RotateMotor(OUT_AB,-10,-240);
	RotateMotor(OUT_A,10,90*2*d/R);
	RotateMotor(OUT_B,-10,-90*2*d/R);
	RotateMotor(OUT_AB,-10,-180);

	time(&str);
	while(true)
	{
		OnFwdReg(OUT_C,100);

		time(&fnsh);
		if(difftime(fnsh,str) > 5)
		{
			break;
		}
	}




	// move robot to finish location close to goal
	// stop the robot
	return true;
}


void FindGoal::reset()
{
	return;
}

void FindGoal::initialize()
{
	LcdPrintf(1, " %s \n","There is a fire" );
	LcdPrintf(1, " %s ", "Call 911!!");
}

/*
 * Destructor
 */
FindGoal::~FindGoal() {}

