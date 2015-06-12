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
        speed = 300;
        presentPos.push_back(dxl_read_word(i, P_PRESENT_POSITION_L));
        speedCorrection = ((goalPos.at(i-1)-presentPos[i])/1024);
        // absolute waarde
        if(speedCorrection<0) speedCorrection *= -1;

        //speeds.push_back(speed*speedCorrection);
        speeds.push_back(speed);
    }

    for(int i=1;i<=18; i++){
        if(i == 1)
        {
            goalPos.at(i - 1) = goalPos.at(i -1) + 15;
        }
        if(i == 11)
        {
            goalPos.at(i - 1) = goalPos.at(i -1) - 15;
        }//dit is om hem iets rechter te laten lopen
        dxl_write_word( i, P_GOAL_SPEED_L, speeds.at(i-1));
        dxl_write_word( i, P_GOAL_POSITION_L, goalPos.at(i-1));
        //std::cout << "goalPos " << i << " = " << goalPos.at(i-1) << std::endl;
    }

    int tmp;
    int inPos = 0;
    int correction = 0;
    while(!inPosition){
        int count;
        for(int i =1; i <= 18; i++){
            tmp = dxl_read_word(i, P_PRESENT_POSITION_L);
            if((tmp >= goalPos.at(i-1) - 30) && (tmp <= goalPos.at(i-1) + 30)){//zet de inpositie boolean op true, wacht tot de servo' s op het eindpunt zijn.
                inPos++;
            }

        }
        if(inPos > 18) inPosition = true;
        else inPos = 1;
    }

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
        getchar();
        //return 0;
    }
    else
    {
        //printf("Succeed to open dynamixel");
    }

    //std::vector<int> testSet{442,669,982,419,691,1002,581,690,990,442,333,990,419,332,1002,581,354,982};//backup eele
    //std::vector<int> testSet{442,772,1009,419,715,1010,581,772,1009,442,310,997,419,242,1023,581,310,997};
    //send(testSet);

    std::vector<std::vector<int>> testSet{
            {442,669,982,419,691,1002,581,690,990,442,333,990,419,332,1002,581,354,982},
            {442,772,1009,419,691,1002,581,772,1009,442,333,990,419,242,1023,581,354,982},
            {380,665,944,419,691,1002,502,691,1002,442,333,990,497,333,987,581,354,982}
            //{512,715,1010,419,715,1010,512,715,1010,512,308,1010,419,308,1010,512,308,1010}

            //{512,512,818,419,512,818,512,512,818,512,512,818,419,512,818,512,512,818},
            //{512,636,911,419,512,818,512,636,911,512,512,818,419,387,911,512,512,818}

    };
    for(int i = 0;i < testSet.size();i++)
    {
        //std::cout << testSet.size() << std::endl;
        send(testSet.at(i));
    }

    std::vector<std::vector<int>> servoPos =
            {
                    {380, 665, 944, 419, 781, 1023, 502, 691, 1002, 442, 251, 1009, 497, 333, 987, 581, 251, 1009},
                    {442, 669, 982, 419, 781, 1023, 581, 690, 990, 442, 251, 1009, 419, 332, 1002, 581, 251, 1009},
                    {521, 667, 993, 419, 781, 1023, 643, 683, 950, 442, 251, 1009, 340, 333, 987, 581, 251, 1009},
                    {521, 667, 993, 340, 690, 987, 643, 683, 950, 521, 332, 1002, 340, 333, 987, 643, 358, 944},
                    {442, 772, 1009, 340, 690, 987, 581, 772, 1009, 521, 332, 1002, 419, 242, 1023, 643, 358, 944},
                    {442, 772, 1009, 419, 691, 1002, 581, 772, 1009, 442, 333, 990, 419, 242, 1023, 581, 354, 982},
                    {442, 772, 1009, 497, 690, 987, 581, 772, 1009, 380, 340, 950, 419, 242, 1023, 502, 356, 993},
                    {380, 665, 944, 497, 690, 987, 502, 691, 1002, 380, 340, 950, 497, 333, 987, 502, 356, 993}

                    /*{498,754,1018,419,715,1010,498,754,1018,512,308,1010,432,269,1018,512,308,1010},
                    {485,691,1000,419,715,1010,485,691,1000,512,308,1010,445,332,1000,512,308,1010},
                    {485,691,1000,405,781,1022,485,691,1000,525,242,1022,445,332,1000,525,242,1022},
                    {512,691,1002,405,781,1022,512,691,1002,525,242,1022,419,332,1002,525,242,1022},
                    {525,691,1002,405,781,1022,525,691,1002,525,242,1022,405,332,1002,525,242,1022},
                    {538,691,1000,392,715,1008,538,691,1000,538,308,1008,392,332,1000,538,308,1008},
                    {498,754,1018,405,715,1009,498,754,1018,525,308,1009,432,269,1018,525,308,1009},
                    {498,754,1018,419,715,1010,498,754,1018,512,308,1010,432,269,1018,512,308,1010},
                    {498,754,1018,432,715,1009,498,754,1018,498,308,1009,432,269,1018,498,308,1009},
                    {485,691,1000,445,715,1008,485,691,1000,485,308,1008,445,332,1000,485,308,1008},
                    {485,691,1000,405,781,1022,485,691,1000,525,242,1022,445,332,1000,525,242,1022},
                    {512,691,1002,405,781,1022,512,691,1002,525,242,1022,419,332,1002,525,242,1022},
                    {498,691,1002,405,781,1022,498,691,1002,525,242,1022,432,332,1002,525,242,1022},
                    {485,691,1000,392,715,1008,485,691,1000,538,308,1008,445,332,1000,538,308,1008}*///mini loopje voor brug :D
            };





    /*std::vector<std::vector<int>> servoPos =
            {
                    {380,701,956,419,781,1023,502,715,1009,442,251,1009,497,311,994,581,251,1009},
                    {442,713,997,419,781,1023,581,713,997,442,251,1009,419,308,1010,581,251,1009},
                    {521,715,1009,419,781,1023,643,701,956,442,251,1009,340,311,994,581,251,1009},
                    {521,715,1009,340,712,994,643,701,956,521,308,1009,340,311,994,643,322,956},
                    {442,772,1009,340,712,994,581,772,1009,521,308,1009,419,242,1023,643,322,956},
                    {442,772,1009,419,715,1010,581,772,1009,442,310,997,419,242,1023,581,310,997},
                    {442,772,1009,497,712,994,581,772,1009,380,322,956,419,242,1023,502,308,1009},
                    {380,701,956,497,712,994,502,715,1009,380,322,956,497,311,994,502,308,1009}
            };*/// backup eele
    for(int j = 0; j<20;j++){//why 20 :( wut dis
        for(int i =0; i<servoPos.size(); i++)
        {
            send(servoPos.at(i));
        }
    }

}