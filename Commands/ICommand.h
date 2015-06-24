//
// Created by eele on 10-6-2015.
//

#ifndef SPIN_ICOMMAND_H
#define SPIN_ICOMMAND_H


#include <vector>
#include <iostream>
#include "../ServoDriver.h"
#include "../Models/ControlData.h"
#include "../Models/SensorData.h"

class ICommand {
public:
    std::string currCSV;
    std::string lastCSV;
    std::vector<std::vector<int>> input;

    ServoDriver *servoDriver;
    ControlData *controlData = nullptr;
    SensorData *sensorData= nullptr;
    int *x;
    int *y;
    int *balloon;

    ICommand(ServoDriver *servoDriver) : servoDriver(servoDriver) {}
    ICommand(ServoDriver *servoDriver, ControlData *controlData) : servoDriver(servoDriver), controlData(controlData) { }
    ICommand(ServoDriver *servoDriver, SensorData *sensorData) : servoDriver(servoDriver), sensorData(sensorData) { }
    ICommand(ServoDriver *servoDriver, SensorData *sensorData,int *x, int *y,int *balloon) : servoDriver(servoDriver), sensorData(sensorData), x(x), y(y), balloon(balloon) { }

    virtual void init()=0;

    virtual void run()=0;
};


#endif //SPIN_ICOMMAND_H