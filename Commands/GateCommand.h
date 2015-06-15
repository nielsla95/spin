//
// Created by root on 15-6-15.
//

#ifndef SPIN_GATECOMMAND_H
#define SPIN_GATECOMMAND_H

#include "ICommand.h"

class GateCommand : public ICommand{
public:
    GateCommand(ServoDriver *servoDriver) : ICommand(servoDriver) { }

    virtual void init() override;

    virtual void run() override;
};

#endif //SPIN_GATECOMMAND_H
