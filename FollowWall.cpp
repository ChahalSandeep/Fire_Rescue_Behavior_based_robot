/*
 * FollowWall.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: Topgear(Sandeep, Cem, Michael, Shreesha)
 */
#include<ev3.h>
#include<ctime>
#include<cstdlib>
#include "FollowWall.h"
#include "Behavior.h"


#define R 0.0275
#define d 0.06

int leftSonar;
int rightSonar;
int straightSonar;

int dir;
int turn_distance = 150;
double delta_t = 0.1;

float rand_dir = 0;


time_t start, finish;
time_t begin, end, init, check;


/*
 * Constructor
 */
FollowWall::FollowWall() {}

/*
 * Implement virtual method from Behavior base
 * class
 */
bool FollowWall::isTriggered()
{
	time(&check);

	if (difftime(check,init) > 40)
	{
		time(&init);
		initialize();
		return false;
	}
	return true;
}

/*
 * Implement virtual method from Behavior base
 * class. Start following a wall.
 * This is behavior will execute
 * for some predetermined amout of time
 * and then stop
 */

bool FollowWall::act()
{
	// execute follow wall routine

	// previous value
	// sonar value current
	// if current value <= previous value
	// the go straight else turn left


	//if ( Behavior::sonar_angle < 60 &&  Behavior::sonar_angle > 30) // following left wall
	if ( Behavior::sonar_angle == 15)
	{
		if (readSensor(IN_1) > 150 && readSensor(IN_1) < 300)
		{
			OnFwdReg(OUT_A,10);
			OnFwdReg(OUT_B,12);
		}
		else if (readSensor(IN_1) > 300)
		{
			OnFwdReg(OUT_A,10);
			OnFwdReg(OUT_B,25);
		}

		else if (readSensor(IN_1) < 130 )
		{
			OnFwdReg(OUT_A,15);
			OnFwdReg(OUT_B,10);
		}


		else
		{
			OnFwdReg(OUT_A,10);
			OnFwdReg(OUT_B,10);
		}


	}

	else if ( Behavior::sonar_angle == 165)
	{
		if (readSensor(IN_1) > 150 && readSensor(IN_1) < 300 )
		{
			OnFwdReg(OUT_A,12);
			OnFwdReg(OUT_B,10);
		}
		else if (readSensor(IN_1) > 300)
		{
			OnFwdReg(OUT_A,25);
			OnFwdReg(OUT_B,10);
		}
		else if (readSensor(IN_1) < 130 )
		{
			OnFwdReg(OUT_A,10);
			OnFwdReg(OUT_B,15);
		}
		else
		{
			OnFwdReg(OUT_A,10);
			OnFwdReg(OUT_B,10);
		}
	}

	else if ( Behavior::sonar_angle == 30 )
	{

		if (readSensor(IN_1) > 150 && readSensor(IN_1) < 300 )
		{
			OnFwdReg(OUT_A,10);
			OnFwdReg(OUT_B,12);
		}
		else if (readSensor(IN_1) > 300)
		{
			OnFwdReg(OUT_A,10);
			OnFwdReg(OUT_B,25);
		}
		else if (readSensor(IN_1) < 130 )
		{
			OnFwdReg(OUT_A,15);
			OnFwdReg(OUT_B,10);
		}
		else
		{
			OnFwdReg(OUT_A,10);
			OnFwdReg(OUT_B,10);
		}

	}

	else if ( Behavior::sonar_angle == 150 )
	{
		if (readSensor(IN_1) > 150 && readSensor(IN_1) < 300 )
		{
			OnFwdReg(OUT_A,12);
			OnFwdReg(OUT_B,10);
		}
		else if (readSensor(IN_1) > 300)
		{
			OnFwdReg(OUT_A,25);
			OnFwdReg(OUT_B,10);
		}
		else if (readSensor(IN_1) < 130 )
		{
			OnFwdReg(OUT_A,10);
			OnFwdReg(OUT_B,15);
		}
		else
		{
			OnFwdReg(OUT_A,10);
			OnFwdReg(OUT_B,10);
		}

	}

	reset();

	return false;
}

void FollowWall::reset()
{


}

void FollowWall::initialize()
{

	time(&init);

	Off(OUT_ABCD);

	Behavior::hit_count++;
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

	RotateMotor(OUT_D,10,15);
	leftSonar = readSensor(IN_1);

	RotateMotor(OUT_D,10,75);
	straightSonar = readSensor(IN_1);

	RotateMotor(OUT_D,10,75);
	rightSonar = readSensor(IN_1);
	//	LcdPrintf(1, " straightsonar: %d ", rightSonar);
	RotateMotor(OUT_D,-10,-75);
	//DETECTING NEAREST WALL
	if (leftSonar < rightSonar && leftSonar < straightSonar)
	{
		//RotateMotor(OUT_A,-10,-90*d/R);
		if (leftSonar > 200)
		{
			RotateMotor(OUT_B,10,90*2*d/R);



			time(&start);
			while(true)
			{
				time(&begin);
				time(&end);

				if(difftime(end,begin) < delta_t)
				{
					Wait((delta_t-difftime(end,begin))*1000);
				}

				if(readSensor(IN_1) > turn_distance )
				{
					OnFwdReg(OUT_A,10);
					OnFwdReg(OUT_B,10);
				}
				else if (readSensor(IN_1) < turn_distance )
				{
					Off(OUT_ABCD);
					RotateMotor(OUT_A,10,90*2*d/R);
					break;
				}

				if ( readSensor(IN_3) == 1 || readSensor(IN_4) ==1 )
				{
					break;
				}

			}

			RotateMotor(OUT_D,-10,-75);
		}

		else if (leftSonar < 100)
		{
			RotateMotor(OUT_D,-10,-75);
		}
		else
		{
			RotateMotor(OUT_D,-10,-60);
		}

	}
	else if ( rightSonar < leftSonar && rightSonar < straightSonar)
	{
		if (rightSonar > 200)
		{
			RotateMotor(OUT_A,10,90*2*d/R);

			time(&start);
			while(true)
			{
				time(&begin);
				time(&end);

				if(difftime(end,begin) < delta_t)
				{
					//LcdPrintf(1, "inside while \n");
					Wait((delta_t-difftime(end,begin))*1000);
				}

				if(readSensor(IN_1) > turn_distance )
				{
					OnFwdReg(OUT_A,10);
					OnFwdReg(OUT_B,10);
				}
				else if (readSensor(IN_1) < turn_distance )
				{
					Off(OUT_ABCD);
					RotateMotor(OUT_B,10,90*2*d/R);
					break;
				}

				if ( readSensor(IN_3) == 1 || readSensor(IN_4) ==1 )
				{
					break;
				}

			}

			RotateMotor(OUT_D,10,75);
		}
		else if (rightSonar < 100 )
		{
			RotateMotor(OUT_D,10,75);
		}
		else
		{
			RotateMotor(OUT_D,10,60);
		}
	}
	else
	{

		if (readSensor(IN_1) < turn_distance )
		{
			RotateMotor(OUT_AB,-10,-180);


			time(&start);
			while(true)
			{
				time(&begin);
				time(&end);

				if(difftime(end,begin) < delta_t)
				{
					//LcdPrintf(1, "inside while \n");
					Wait((delta_t-difftime(end,begin))*1000);
				}

				if(readSensor(IN_1) > turn_distance )
				{
					OnFwdReg(OUT_A,10);
					OnFwdReg(OUT_B,10);
					//LcdPrintf(1, " sonar: %d ", readSensor(IN_1));

				}
				else if (readSensor(IN_1) < turn_distance )
				{
					Off(OUT_ABCD);
					//RotateMotor(OUT_A,-10,-90*d/R);

					rand_dir = ((double) rand()/RAND_MAX);

					if (rand_dir > 0.5 )
					{
						RotateMotor(OUT_B,10,90*2*d/R);
						dir = 1; //1 means you turned left
					}
					else
					{
						RotateMotor(OUT_A,10,90*2*d/R);
						dir = 0;//0 means you turned right
					}
					break;
				}

				if ( readSensor(IN_3) == 1 || readSensor(IN_4) ==1 )
				{
					break;
				}

			}
			if ( dir == 1)
			{
				RotateMotor(OUT_D,10,75);
			}
			else if ( dir == 0)
			{
				RotateMotor(OUT_D,-10,-75);
			}

		}

		else
		{


			time(&start);
			while(true)
			{
				time(&begin);
				time(&end);

				if(difftime(end,begin) < delta_t)
				{
					//LcdPrintf(1, "inside while \n");
					Wait((delta_t-difftime(end,begin))*1000);
				}

				if(readSensor(IN_1) > turn_distance )
				{
					OnFwdReg(OUT_A,10);
					OnFwdReg(OUT_B,10);
					//LcdPrintf(1, " sonar: %d ", readSensor(IN_1));

				}
				else if (readSensor(IN_1) < turn_distance )
				{
					Off(OUT_ABCD);
					//RotateMotor(OUT_A,-10,-90*d/R);
					rand_dir = ((double) rand()/RAND_MAX);

					if (rand_dir > 0.5 )
					{
						RotateMotor(OUT_B,10,90*2*d/R);
						dir = 1; //1 means you turned left
					}
					else
					{
						RotateMotor(OUT_A,10,90*2*d/R);
						dir = 0;//0 means you turned right
					}
					break;
				}

				if ( readSensor(IN_3) == 1 || readSensor(IN_4) ==1 )
				{
					break;
				}

			}

			if ( dir == 1)
			{
				RotateMotor(OUT_D,10,75);
			}
			else if ( dir == 0)
			{
				RotateMotor(OUT_D,-10,-75);
			}


		}


	}

}


/*
 * Destructor
 */
FollowWall::~FollowWall() {}

