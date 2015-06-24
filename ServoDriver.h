//
// Created by eele on 9-6-2015.
//

#ifndef SPIN_SERVODRIVER_H
#define SPIN_SERVODRIVER_H

#include <thread>
#include <vector>

class ServoDriver {

public:
    ServoDriver(std::vector<int> *servoData):servoData(servoData){
        init();
    };
    int logCounter = 0;
    std::vector<int> *servoData;
    virtual ~ServoDriver() {}
    void PrintCommStatus(int CommStatus);
    void PrintErrorCode();
    void doOne(int num, int GoalPos, int speed);
    void getData();
    void sendSyncWrite(std::vector<std::vector<int>> goalPos,int sleepTime, int speed);
    bool send(std::vector<std::vector<int>> goalPos);
    bool send(std::vector<std::vector<int>> goalPos, int _speed, int _speed_min,        bool useCheck);

    void logSendSynceWrite(std::vector < std::vector < int >> goalPos,int sleepTime, int speed);
    void init();
};


#endif //SPIN_SERVODRIVER_H
