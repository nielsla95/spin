//
// Created by root on 15-6-15.
//

#ifndef SPIN_POLECOMMAND_H
#define SPIN_POLECOMMAND_H

#include "ICommand.h"

class PoleCommand : public ICommand{
public:

    PoleCommand(ServoDriver *servoDriver, SensorData *sensorData) : ICommand(servoDriver, sensorData) { }

    virtual void init() override;

    virtual void run() override;
};


#endif //SPIN_POLECOMMAND_H
