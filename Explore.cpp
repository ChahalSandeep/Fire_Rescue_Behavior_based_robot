/*
 * Explore.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear
 */

#include<ev3.h>
#include<cstdlib>
#include<ctime>
#include "Explore.h"


#define R 0.0275
#define d 0.06

int leftS;
int rightS;
int straightS;

float r = 0;
bool complete = true;

time_t init2, check2;


/*
 * Constructor
 */
Explore::Explore() {
	//LcdPrintf(1, "In explore ");
}


/*
 * Implement virtual method from Behavior base
 * class
 */
bool Explore::isTriggered()
{
	// nothing to do here.
	// explore does not use sensors
	// always return true

	if(!complete || Behavior::hit_count == 3)
	{
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
bool Explore::act()
{
	OnFwdReg(OUT_A,20);
	OnFwdReg(OUT_B,20);

	if (readSensor(IN_1) < 150 )
	{
		reset();
	}



	return false;
}

void Explore::reset()
{
	complete = true;
}

void Explore::initialize()
{
	LcdPrintf(1, "%s\n", "Exploring...");
	Off(OUT_ABCD);
	complete = false;
	Behavior::hit_count = 0;

	if(Behavior::sonar_angle != 0)
	{
		if (Behavior::sonar_angle > 0)
		{
			RotateMotor(OUT_D,-10,-Behavior::sonar_angle );
			//LcdPrintf(1, " sonar2: %d ", Behavior_object.sonar_angle);
		}
		else if (Behavior::sonar_angle < 0)
		{
			RotateMotor(OUT_D,10,-Behavior::sonar_angle );
		}
	}

	leftS = readSensor(IN_1);
	//	LcdPrintf(1, " leftsonar: %d ", leftSonar);
	RotateMotor(OUT_D,10,90);
	straightS = readSensor(IN_1);
	//	LcdPrintf(1, " straightsonar: %d ", straightSonar);
	RotateMotor(OUT_D,10,90);
	rightS = readSensor(IN_1);
	//	LcdPrintf(1, " straightsonar: %d ", rightSonar);
	RotateMotor(OUT_D,-10,90);
	//DETECTING NEAREST WALL

	if (leftS < rightS )
	{
		r = 90 + ((int) rand() % 90);
	}
	else if (leftS > rightS  )
	{
		r = ((int) rand() % 90);
	}
	else
	{
		r = 90;
	}


	if ( r > 90)
	{
		RotateMotor(OUT_A,10,2*d*(90-r)/R);
	}
	else
	{
		RotateMotor(OUT_B,10,2*d*(r-90)/R);
	}

}


Explore::~Explore() {}
