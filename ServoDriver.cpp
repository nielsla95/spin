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
#define P_SPEED 		50

unsigned char Moving;
int PresentPos;

void PrintCommStatus(int CommStatus)
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

void PrintErrorCode()
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

void doOne(int num, int GoalPos, int speed){
    dxl_write_word( num, P_GOAL_SPEED_L, speed);
    dxl_write_word( num, P_GOAL_POSITION_L, GoalPos );
}

void init()
{
    int baudnum = 1;
    int deviceIndex = 0;
    if(dxl_initialize(deviceIndex, baudnum) == 0)
    {
        printf("Faild to open dynamixel");
        printf("Press enter to terminate \n");
        getchar();
        //return 0;
    }
    else
    {
        //printf("Succeed to open dynamixel");
    }
}

void moveYourLegs(int PS[][18], int numberOfPositions)
{


    int GoalPos;
    int servoid;
    int tmp;
    int i;
    int j;

    // magic stuff
    for(i = 0  ;i < numberOfPositions ;i++)
    {
        int servosnotmoving = 0;
//			printf(" %d" , i);
        {
            servoid = i+1;
            //	GoalPos = PS[i][j];
            /*		if(i >= 1)
                        tmp = i -1;
                    else
                        tmp = numberOfPositions - 1 ;

                */
            Moving = dxl_read_byte(servoid, P_MOVING);
            printf("MOVING? %d\n", Moving);
            //usleep(1000);

            if(Moving == 0){
                printf("not moving \n");
                PresentPos = dxl_read_word(servoid, P_PRESENT_POSITION_L);
                if((PresentPos <= PS[tmp][j] + 5 && PresentPos >= PS[tmp][j] - 5) || i == 0){
                    Moving = dxl_read_byte( servoid, P_MOVING );
                    //printf("go to next");
                    doOne(servoid, GoalPos, P_SPEED);
                    servosnotmoving++;

                    Moving = dxl_read_byte( servoid, P_MOVING );
                    printf("Servo not moving is %d\n", servosnotmoving);
                }
            }

            //doOne(servoid, GoalPos, 100);
            //Moving = dxl_read_byte( servoid, P_MOVING );
            //PresentPos = dxl_read_word( servoid, P_PRESENT_POSITION_L );
            //printf("Servo %d = %d and is going to be %d %d\n", servoid, PresentPos, GoalPos, Moving);
            PrintErrorCode();
        }
        servosnotmoving = 18;
        float Speed;
        if(servosnotmoving ==18){
            for(j = 0  ;j < 18 ;j++)
            {	float ExtraSpeed = ((GoalPos-PresentPos)/100);
                printf("ExtraSpeed = %f\n", ExtraSpeed);
                servoid = j+1;
                GoalPos = PS[i][j];
                //P_SPEED = P_SPEED + ExtraSpeed;

                Speed = (float)P_SPEED*ExtraSpeed;
                if (Speed<=0){
                    if (Speed == 0) Speed = 50;
                    else
                        Speed =0-Speed;

                }

                printf("Servo %d Speed is: %f\n",j, P_SPEED);


                doOne(servoid, GoalPos, (P_SPEED));
                //if(j %3 == 0)
                //{
                //getchar();
                //}
                sleep(1);
            }
            servosnotmoving = 0;
//				usleep(500000);
        }
        else{
            i--;
        }
        //usleep(1000);
        getchar();
    }


}
