/*
 * Escape.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear
 */

#include "Escape.h"
#include "ev3.h"
#include "Behavior.h"

#define R 0.0275
#define d 0.06

int left;
int right;
int straight;

int leftHit;
int rightHit;
int bothHit;

/*
 * Constructor
 */
Escape::Escape() {}


/*
 * Implement virtual method from Behavior base
 * class
 * Listen on the touch sensor to detect a collision
 */
bool Escape::isTriggered()
{
	if ( readSensor(IN_3) == 1 && readSensor(IN_4) ==1 )
	{
		bothHit = 1;
		return true;
	}
	else if (readSensor(IN_3) == 1)
	{
		leftHit = 1;
		return true;
	}
	else if (readSensor(IN_4) ==1 )
	{
		rightHit = 1;
		return true;
	}

	return false;
}

/*
 * Implement virtual method from Behavior base
 * class
 * Activated by touch sensors
 * This is the action the robot will take when in
 * this behavior. Escape will stop, backup, and turn at a
 * random angle such that it will not go back to the direction
 * it was facing when it stopped. (Ran into something)
 */
bool Escape::act()
{
	if (bothHit == 1 )
	{
		label:
		Off(OUT_AB);
		RotateMotor(OUT_AB,-10,-180);
		Behavior::sonar_angle = MotorRotationCount(OUT_D);

		if(Behavior::sonar_angle != 0)
		{
			if (Behavior::sonar_angle > 0)
			{
				RotateMotor(OUT_D,-10,-Behavior::sonar_angle );
			}
			else if (Behavior::sonar_angle < 0)
			{
				RotateMotor(OUT_D,10,-Behavior::sonar_angle );
			}
		}
		RotateMotor(OUT_D,10,15);
		left = readSensor(IN_1);
		RotateMotor(OUT_D,10,75);
		straight = readSensor(IN_1);
		RotateMotor(OUT_D,10,75);
		right = readSensor(IN_1);
		RotateMotor(OUT_D,-10,-75);
		//DETECTING NEAREST WALL

		if (left < right && right > 250 )
		{
			RotateMotor(OUT_A,10,90*2*d/R);
		}
		else if (left > right && left > 250 )
		{
			RotateMotor(OUT_B,10,90*2*d/R);
		}
		else if ((left < 200 && right < 200))
		{
			reset();
			goto label;

		}

	}

	else if (leftHit == 1)
	{
		Off(OUT_AB);
		RotateMotor(OUT_AB,-10,-60);
		RotateMotor(OUT_A,10,30*2*d/R);
		reset();
		goto label;
	}

	else if (rightHit == 1)
	{
		Off(OUT_AB);
		RotateMotor(OUT_AB,-10,-60);
		RotateMotor(OUT_B,10,30*2*d/R);
		reset();
		goto label;
	}

	// we are done with escape so reset
	reset();
	return false;
}

void Escape::reset()
{
	bothHit = 0;
	leftHit = 0;
	rightHit = 0;
}

void Escape::initialize()
{
	//LcdPrintf(1, "%s\n", "Catch me");
}
/*
 * Destructor
 */
Escape::~Escape() {}
