//
// Created by eele on 9-6-2015.
//

#ifndef SPIN_SERVODRIVER_H
#define SPIN_SERVODRIVER_H

#include <thread>
#include <vector>

class ServoDriver {

public:
    ServoDriver(){
        init();
    };
    virtual ~ServoDriver() {}

    void PrintCommStatus(int CommStatus);
    void PrintErrorCode();
    void doOne(int num, int GoalPos, int speed);
    bool send(std::vector<std::vector<int>> goalPos);
    bool send(std::vector<std::vector<int>> goalPos, int _speed, int _speed_min, bool useCheck);
    void init();
};


#endif //SPIN_SERVODRIVER_H
