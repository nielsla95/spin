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

#define PI	3.141529f

// Control table address
#define P_GOAL_POSITION_L       30
#define P_GOAL_SPEED_L          32
#define P_PRESENT_POSITION_L    36
#define P_MOVING 		        46
#define NUM_ACTUATOR		    18
#define DELAY           		(1000) // usec (Large value is more slow)

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

void ServoDriver::sendSyncWrite(std::vector < std::vector < int >> goalPos, int speed) {

    if(speed < 0 || speed > 300) speed = 300;

    int CommStatus;
    for (int j = 0; j < goalPos.size(); ++j) {
        // Make syncwrite packet
        dxl_write_word( BROADCAST_ID, P_GOAL_SPEED_L, speed );
        dxl_set_txpacket_id(BROADCAST_ID);
        dxl_set_txpacket_instruction(INST_SYNC_WRITE);
        dxl_set_txpacket_parameter(0, P_GOAL_POSITION_L);
        dxl_set_txpacket_parameter(1, 2);

        for(int i=0; i<NUM_ACTUATOR; i++ )
        {
            dxl_set_txpacket_parameter(2+3*i,i+1);
            dxl_set_txpacket_parameter(2+3*i+1, dxl_get_lowbyte(goalPos.at(j).at(i)));
            dxl_set_txpacket_parameter(2+3*i+2, dxl_get_highbyte(goalPos.at(j).at(i)));
        }
        dxl_set_txpacket_length((2+1)*NUM_ACTUATOR+4);
        dxl_txrx_packet();
        usleep(1000);
        PrintErrorCode();
        CommStatus = dxl_get_result();
        if( CommStatus == COMM_RXSUCCESS )
        {
            std::cout << "SUCCES COMMSTATUS" << std::endl;
            PrintErrorCode();
        }
        else
        {
            std::cout << "FAIL COMMSTATUS" << std::endl;
            PrintCommStatus(CommStatus);
        }

        // Tijd om beweging af te maken
        float timeOut = 1;

        std::vector<int> presentPos;
        int maxDeltaPos=0;
        int dPos = 0;
        for (int k = 1; k <=18; ++k) {
            dPos = abs(dxl_read_word(k, P_PRESENT_POSITION_L));
            if( dPos>maxDeltaPos) maxDeltaPos = dPos;
        }
        std::cout << "maxDeltaPos: " << maxDeltaPos << std::endl;
        timeOut = maxDeltaPos/((speed*1228)/1023);
        std::cout << "TImeout : "<<timeOut << std::endl;
        usleep(timeOut*1000000);
    }
}

bool ServoDriver::send(std::vector<std::vector<int>> goalPos) {
    return send(goalPos,200,100,true);
}

bool ServoDriver::send(std::vector<std::vector<int>> goalPos, int _speed, int _speed_min, bool useCheck) {
        for (int k = 0; k < goalPos.size(); ++k)
        {
            int speed;
            float dDistance;
            std::vector<int> speeds;
            std::vector<int> presentPos;

            bool inPosition = false;
            for (int i = 1; i <= 18; i++) {
                presentPos.push_back(dxl_read_word(i, P_PRESENT_POSITION_L));
                usleep(1000);
                // deltaDistance
                if (goalPos.at(k).at(i - 1) > presentPos.at(i - 1)) {
                    dDistance = goalPos.at(k).at(i - 1) - presentPos.at(i - 1);
                } else {
                    dDistance = presentPos.at(i - 1) - goalPos.at(k).at(i - 1);
                }

                speed = _speed * (dDistance / 1024);
                if (speed < _speed_min || speed > 1023)speed = _speed_min;

                //std::cout << "CurrentPOs: " << presentPos.at(i - 1) << " GoalPos: " << goalPos.at(k).at(i - 1) << " dDistance: " << dDistance << " speed = " << speed << std::endl;
                speeds.push_back(speed);
            }
            PrintErrorCode();
            for (int i = 1; i <= 18; i++) {
                if (goalPos.at(k).at(i - 1) == 1023) goalPos.at(k).at(i - 1) = 1022;
                // todo: sleeps weghalen en testen
                dxl_write_word(i, P_GOAL_SPEED_L, speeds.at(i - 1));
                usleep(1000);
                PrintErrorCode();

                dxl_write_word(i, P_GOAL_POSITION_L, goalPos.at(k).at(i - 1));
                usleep(1000);
                PrintErrorCode();
            }

            std::cout << "Usecheck : " << useCheck << std::endl;
            if (useCheck) {
                // CHECK MOVING 1
//            char moving = 1;
//            int inPos;
//            while (inPos != 18) {
//                inPos = 0;
//                for (int i = 1; i <= 18; ++i) {
//                    moving = dxl_read_byte(i, P_MOVING);
//                    if (moving == 0) inPos++;
//                }
//                std::cout << "Moving servo's" << std::endl;
//            }

                // EINDE CHECK MOVING 1;

                // CHECK MOVING 2
                int tmp;
                int inPos = 1;
                int accuracy = 25;

                while(!inPosition){
                    for(int i =1; i <= 18; i++){
                        tmp = dxl_read_word(i, P_PRESENT_POSITION_L);
                        usleep(1000);
                        PrintErrorCode();
                        if((tmp >= goalPos.at(k).at(i-1) - accuracy) && (tmp <= goalPos.at(k).at(i-1) + accuracy)){//zet de inpositie boolean op true, wacht tot de servo' s op het eindpunt zijn.
                            inPos++;
                        }
                    }
                    if(inPos >= 18) inPosition = true;
                    else inPos = 1;
                }
                //  EINDE CHECK MOVING 2
            }

            speeds.clear();
            presentPos.clear();
            usleep(DELAY);
        }
    std::cout << "Done sending" << std::endl;
        return true;
}


void ServoDriver::init()
{
    int baudnum = 1;
    int deviceIndex = 0;
    if(dxl_initialize(deviceIndex, baudnum) == 0)
    {
        printf("Faild to open dynamixel");
        printf("Press enter to terminate \n");
    }
    else {
        std::cout<<"Succeed to open dynamixel"<<std::endl;
        printf("Succeed to open dynamixel");
    }
}