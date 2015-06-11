//
// Created by eele on 10-6-2015.
//

#ifndef SPIN_ICOMMAND_H
#define SPIN_ICOMMAND_H


#include <vector>
#include <iostream>
#include "../ServoDriver.h"

class ICommand {
public:
    ICommand(ServoDriver *servoDriver) : servoDriver(servoDriver) { }

    std::vector<int> servoPos;
    ServoDriver *servoDriver;

    virtual void init()=0;

    virtual void run()=0;
};


#endif //SPIN_ICOMMAND_H