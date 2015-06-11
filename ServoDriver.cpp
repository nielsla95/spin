//
// Created by eele on 9-6-2015.
//

#include "ServoDriver.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <termio.h>
#include <iostream>
#include <thread>
#include "dynamixel.h"
//#include <dxl_hal.h>

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
#define CONTROL_PERIOD		1000

#define AMOUNT_SERVOS 		1
#define P_SPEED 		50

unsigned char Moving;
int PresentPos;

void ServoDriver::PrintCommStatus(int CommStatus)
{
    switch(CommStatus)
    {
        case COMM_TXFAIL:
            printf("COMM_TXFAIL: Failed transmit instruction packet!\n");
            break;

        case COMM_TXERROR:
            printf("COMM_TXERROR: Incorrect instruction packet!\n");
            break;

        case COMM_RXFAIL:
            printf("COMM_RXFAIL: Failed get status packet from device!\n");
            break;

        case COMM_RXWAITING:
            printf("COMM_RXWAITING: Now recieving status packet!\n");
            break;

        case COMM_RXTIMEOUT:
            printf("COMM_RXTIMEOUT: There is no status packet!\n");
            break;

        case COMM_RXCORRUPT:
            printf("COMM_RXCORRUPT: Incorrect status packet!\n");
            break;

        default:
            printf("This is unknown error code!\n");
            break;
    }
}

void ServoDriver::PrintErrorCode()
{
    if(dxl_get_rxpacket_error(ERRBIT_VOLTAGE) == 1)
        printf("Input voltage error!\n");

    if(dxl_get_rxpacket_error(ERRBIT_ANGLE) == 1)
        printf("Angle limit error!\n");

    if(dxl_get_rxpacket_error(ERRBIT_OVERHEAT) == 1)
        printf("Overheat error!\n");

    if(dxl_get_rxpacket_error(ERRBIT_RANGE) == 1)
        printf("Out of range error!\n");

    if(dxl_get_rxpacket_error(ERRBIT_CHECKSUM) == 1)
        printf("Checksum error!\n");

    if(dxl_get_rxpacket_error(ERRBIT_OVERLOAD) == 1)
        printf("Overload error!\n");

    if(dxl_get_rxpacket_error(ERRBIT_INSTRUCTION) == 1)
        printf("Instruction code error!\n");
}

void ServoDriver::init()
{
    int baudnum = 1;
    int deviceIndex = 0;
    if(dxl_initialize(deviceIndex, baudnum) == 0)
    {
        printf("Faild to open dynamixel \n");
        printf("Press enter to terminate \n");
        getchar();
        //return 0;
    }
    else
    {
        //printf("Succeed to open dynamixel");
    }
}

void ServoDriver::doOne(int num, int GoalPos, int speed){
    dxl_write_word( num, P_GOAL_SPEED_L, speed);
    dxl_write_word( num, P_GOAL_POSITION_L, GoalPos );
}