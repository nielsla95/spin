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
#include <sys/socket.h>
#include <fstream>
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


void ServoDriver::getData() {
    // layout getData
    // eerste 18(0-17) waardes: verdraaiing
    // tweede 18(18-35) waardes: temp
    // derde 18(36-55) waardes: ???

    std::vector<int> result;
    for (int i = 0; i < 20; ++i) {
        result.push_back(i);
    }
//    for (int i = 1; i <= 18; i++) {
//        for (int i = 1; i <= 18; i++) {
//            result.push_back(dxl_read_word(i, P_PRESENT_POSITION_L));
//        }
//        result.push_back(dxl_read_word(i, P_PRESENT_POSITION_L));
//    }
//    for (int i = 1; i <= 18; i++) {
//        result.push_back(dxl_read_word(i, P_PRESENT_POSITION_L));
//    }

    this->servoData = &result;
    std::cout <<" JOEPIE IK HEB DATA GESTUURD VIA GET DATA" << std::endl;
}

void ServoDriver::sendSyncWrite(std::vector < std::vector < int >> goalPos,int sleepTime, int speed) {

    int dDistance;
    int mDistance=0;
    int juisteServo=0;
    int CommStatus;
    for (int j = 0; j < goalPos.size(); ++j) {

        for (int k = 0; k < goalPos.at(j).size(); ++k) {
            dDistance = abs(goalPos.at(j).at(k) - dxl_read_word(k+1, P_PRESENT_POSITION_L));
            if(dDistance > mDistance){
                mDistance = dDistance;
                juisteServo = k+1;
            }
        }

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


        // check
        // laatste servo lezen
//        int pos = dxl_read_byte(juisteServo, P_PRESENT_POSITION_L);
//        int newPos = goalPos.at(j).at(juisteServo-1);
//        std::cout << "pos: " << pos <<  " -newpos: " << newPos <<std::endl;
//        while(pos==newPos){
//            pos = dxl_read_byte(juisteServo, P_PRESENT_POSITION_L);
//            usleep(1000);
//        }

        // servoData for the serverhandler
        getData();

        usleep(sleepTime);
    }

    // waardes loggen
    // todo: aanzetten als ik wil loggen
    // this->logSendSynceWrite(goalPos,sleepTime,speed);
}


void ServoDriver::logSendSynceWrite(std::vector<std::vector<int >> goalPos, int sleepTime, int speed) {
    /*
     * std::vector<std::vector<int>> anaalzen{
            {370,784,253,274,795,270,366,773,234,292,248,226,275,277,227,362,277,229},
            {370,513,497,274,794,270,366,773,233,292,248,226,275,279,227,363,278,229},
            {369,511,496,274,794,270,367,773,234,292,248,226,275,280,227,374,522,506},
            {369,511,496,281,507,511,367,773,233,292,248,226,275,289,227,374,523,505},
            {369,511,496,281,507,511,367,773,233,292,248,226,284,524,512,374,523,505},
            {369,511,496,282,507,511,372,512,517,292,248,226,284,524,512,374,523,505},
            {372,511,496,280,507,511,372,512,517,358,509,515,269,524,512,366,524,505},
            {522,703,885,411,699,871,514,722,918,508,296,924,426,316,918,405,303,937},
            {522,703,885,411,699,871,514,722,918,508,296,924,426,316,918,504,303,937},
            {513,682,995,400,676,1001,503,671,1017,519,334,964,435,346,962,526,335,986}
    };
     */
    std::ofstream myfile("/home/urmom/logsyncwrite.txt",std::fstream::app);
    if(!myfile){
        std::cout << "NO LOG FILE FOUND" << std::endl;
    }

    myfile << "std::vector<std::vector<int>> goalPos"<<logCounter<< "{\n";
    
    for (int i = 0; i < goalPos.size(); ++i) {
        myfile << "{";
        for (int j = 0; j < goalPos.at(i).size(); ++j) {
            if(j-1!=goalPos.at(i).size()){
                myfile << goalPos.at(i).at(j) << ",";
            }
        }
        if(i-1!=goalPos.at(i).size()) {
            myfile << "},\n";
        }else{
            myfile << "}\n";
        }
    }

    myfile << "};\nint sleepTime"<<logCounter<<"="<< sleepTime<< ";\nint speed"<<logCounter<<"="<<speed<<";\n\n";
    myfile << "this->servoDriver->sendSyncWrite(goalPos"<<logCounter<<",sleepTime"<<logCounter<<",speed"<<logCounter<<");";
    myfile << "\n\n";
    myfile.close();
    logCounter++;
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
            dDistance = abs(goalPos.at(k).at(i - 1) - presentPos.at(i - 1));

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