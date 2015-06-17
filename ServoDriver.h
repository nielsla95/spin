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
    bool send(std::vector<int> goalPos);
    void sendMultiple(std::vector<std::vector<int>> ps);
    void init();
};


#endif //SPIN_SERVODRIVER_H
