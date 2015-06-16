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
#include <utime.h>
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

void ServoDriver::doOne(int num, int GoalPos, int speed){
    dxl_write_word( num, P_GOAL_SPEED_L, speed);
    dxl_write_word( num, P_GOAL_POSITION_L, GoalPos );
}

bool ServoDriver::send(std::vector<int> goalPos) {

    int speed;
    int speedCorrection;
    std::vector<int> speeds;
    std::vector<int> presentPos;

    bool inPosition = false;
    for(int i =1; i <= 18; i++){
        speed = 200;
        presentPos.push_back(dxl_read_word(i, P_PRESENT_POSITION_L));
        usleep(1000);
        speedCorrection = ((goalPos.at(i-1)-presentPos[i])/1024);
        // absolute waarde
        if(speedCorrection<0) speedCorrection *= -1;

        //speeds.push_back(speed*speedCorrection);
        speeds.push_back(speed);
    }

    for(int i=1;i<=18; i++){
        dxl_write_word( i, P_GOAL_SPEED_L, speeds.at(i-1));
        usleep(1000);
        dxl_write_word( i, P_GOAL_POSITION_L, goalPos.at(i-1));
        usleep(1000);
    }

    int tmp;
    int inPos = 0;

    while(!inPosition){

        for(int i =1; i <= 18; i++){
            tmp = dxl_read_word(i, P_PRESENT_POSITION_L);
            if((tmp >= goalPos.at(i-1) - 100) && (tmp <= goalPos.at(i-1) + 100)){//zet de inpositie boolean op true, wacht tot de servo' s op het eindpunt zijn.
                inPos++;
            }
        }
        if(inPos >= 18) inPosition = true;
        else inPos = 1;
    }

    return true;
}

void ServoDriver::sendMultiple(std::vector<std::vector<int>> ps) {
    for (int i = 0; i < ps.size(); ++i) {
        send(ps.at(i));
    }
}

void ServoDriver::init()
{
    int baudnum = 1;
    int deviceIndex = 0;
    if(dxl_initialize(deviceIndex, baudnum) == 0)
    {
        printf("Faild to open dynamixel");
        printf("Press enter to terminate \n");
        //getchar();
        //return 0;
    }
    else {
        std::cout<<"Succeed to open dynamixel"<<std::endl;
        printf("Succeed to open dynamixel");
    }
}