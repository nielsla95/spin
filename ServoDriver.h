//
// Created by eele on 9-6-2015.
//

#ifndef SPIN_SERVODRIVER_H
#define SPIN_SERVODRIVER_H

#include <thread>

class ServoDriver {

public:
    std::thread servoThread;
    ServoDriver() { servoThread = std::thread(&ServoDriver::init,this);}
    virtual ~ServoDriver() { servoThread.join(); }

    void PrintCommStatus(int CommStatus);
    void PrintErrorCode();
    void doOne(int num, int GoalPos, int speed);
    void moveYourLegs(int PS[][18], int numberOfPositions);
    void init();
};


#endif //SPIN_SERVODRIVER_H
