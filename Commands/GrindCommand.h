//
// Created by root on 18-6-15.
//

#ifndef SPIN_GRINDCOMMAND_H
#define SPIN_GRINDCOMMAND_H


#include "ICommand.h"
#include "../ServoDriver.h"

class GrindCommand : public ICommand{
public:
    GrindCommand(ServoDriver *servoDriver) : ICommand(servoDriver) { }

    virtual void init() override;

    virtual void run() override;
};


#endif //SPIN_GRINDCOMMAND_H
