/*
 * Controller.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear(Sandeep, Cem, Michael, Shreesha)
 */
#include<ev3.h>
#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cmath>
#include "Behavior.h"
#include "Escape.h"
#include "Avoid.h"
#include "FindGoal.h"
#include "Explore.h"
#include "FollowWall.h"

#define R 0.0275
#define d 0.06
#define N 5 // Number of behaviours

using namespace std;

void initialize();
void shutdown();

int Behavior::sonar_angle = 0, Behavior::hit_count = 0;

/*
 * Create a list of the 4 behaviors in order of priority
 * for each behavior, starting with higest priority,
 * If it has been triggered, call its act method
 *
 * FindGoal behavior will return true from the act() method
 * when it has competed and we are done
 *
 * list of prioritized behaviors
 * 0 = Escape
 * 1 = Avoid
 * 2 = FindGoal
 * 3 = Explore
 * 4 = FollowWall
 *
 */
int main()
{
	initialize();

	// ----------------------------------------------
	// Create a prioritized list of our 5 behaviors
	// ----------------------------------------------
	Behavior *behaviors[] = {new Escape(), new FindGoal(), new Avoid(), new Explore(), new FollowWall() };

	int current = 0;
	double delta_t = 0.1;
	bool done = false;

	Behavior::sonar_angle = 0;
	time_t start, finish;
	time_t begin, end;


	time(&start);
	// loop over the behaviors and check if they have been triggered by a sensor
	while(!done)
	{

		time(&begin);

		time(&end);

		if(difftime(end,begin) < delta_t)
		{
			//LcdPrintf(1, "inside while \n");
			Wait((delta_t-difftime(end,begin))*1000);
		}

		for(int i = 0; i < N; i++)
		{
			// if the current behavior got usurped, reset it
			// and set current = to higher priority behavior
			if(behaviors[i]->isTriggered())
			{
				if(current != i)
				{
					behaviors[i]->reset();
					current = i;
					behaviors[i]->initialize();
				}
				//call act on current behavior. FindGoal returns true when it finishes
				done = behaviors[i]->act();
				i = 0; // reset i to go back to highest priority
				break;
			}
		}

		if (ButtonIsDown(BTNEXIT)) {
			break;
		}

		Behavior::sonar_angle = MotorRotationCount(OUT_D);
	}

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

	LcdPrintf(1, "%s\n", "Exited the while loop");
	Wait(5000);
	shutdown();

}

/*
 * Initialize EV3 Robot
 */
void initialize()
{
	InitEV3();
	setAllSensorMode(US_DIST_MM, COL_COLOR ,TOUCH_PRESS, TOUCH_PRESS);
	ResetRotationCount(OUT_ABCD);
}


void shutdown()
{
	FreeEV3();
}

