/*
 * Avoid.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear(Sandeep, Cem, Michael, Shreesha)
 */

#include <ev3.h>
#include "Avoid.h"


using namespace std;

/*
 * Constructor
 */
Avoid::Avoid() {}

/*
 * Implement virtual method from Behavior base
 * class
 * Listen on the sensor to detect an obstacle
 */
bool Avoid::isTriggered()
{
	// Because we are just turning to avoid a wall,
	// for Avoid, we can just use the sensor reading,
	// so if the sensor is detecting an obstacle, then
	// simply return true.
	// If the sensor is no longer seeing the obstacly,
	// then just return false.

		return false;

}

/*
 * Implement virtual method from Behavior base
 * class
 * This is the action the robot will take when in
 * this behavior which is to avoid obstacles
 */
bool Avoid::act()
{

	//Wait(5000);
	//LcdPrintf(1, " %d ", readSensor(IN_1));
	//OnRevReg(OUT_AB, 30);
	//OnFwdReg(OUT_B, -30);
	return false;
}

void Avoid::reset()
{
	//Off(OUT_AB);
}

void Avoid::initialize()
{
	LcdPrintf(1, "%s\n", "Avoiding");
}


/*
 * Destructor
 */
Avoid::~Avoid() {}

