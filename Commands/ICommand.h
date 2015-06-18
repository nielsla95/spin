//
// Created by eele on 10-6-2015.
//

#ifndef SPIN_ICOMMAND_H
#define SPIN_ICOMMAND_H


#include <vector>
#include <iostream>
#include "../ServoDriver.h"
#include "../Models/ControlData.h"
struct Point{
    int x;
    int y;
};
class ICommand {
public:
    std::string currCSV;
    std::string lastCSV;

    ICommand(ServoDriver *servoDriver) : servoDriver(servoDriver) {}
    ICommand(ServoDriver *servoDriver, ControlData *controlData) : servoDriver(servoDriver), controlData(controlData) { }

    ServoDriver *servoDriver;
    ControlData *controlData = nullptr;

    virtual void init()=0;

    virtual void run()=0;
};


#endif //SPIN_ICOMMAND_H