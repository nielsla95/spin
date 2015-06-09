//
// Created by eele on 9-6-2015.
//

#ifndef SPIN_SERVODRIVER_H
#define SPIN_SERVODRIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <termio.h>
#include "include/dynamixel.h"

#define PI	3.141529f

// Control table address
#define P_GOAL_POSITION_L       30
#define P_GOAL_POSITION_H       31
#define P_GOAL_SPEED_L          32
#define P_GOAL_SPEED_H          33
#define P_PRESENT_POSITION_L    36
#define P_PRESENT_POSITION_H	37
#define P_MOVING 		46

#define DEFAULT_BAUDNUM 	1
#define STEP_THETA		(PI / 50.0f)
#define CONTROL_PERIOD		100

#define AMOUNT_SERVOS 		1
#define P_SPEED 		200
//typedef int Moving;
#define true 1
#define false 0
unsigned char Moving;
int PresentPos;

class ServoDriver {
private:
    void PrintCommStatus(int CommStatus);
public:

};


#endif //SPIN_SERVODRIVER_H
