//
// Created by eele on 10-6-2015.
//

#ifndef SPIN_WALKCOMMAND_H
#define SPIN_WALKCOMMAND_H


#include "ICommand.h"

class WalkCommand : public ICommand{
public:
    WalkCommand(ServoDriver *servoDriver, ControlData *controlData) : ICommand(servoDriver,controlData) { }

    virtual void init() override;

    virtual void run() override;
};


#endif //SPIN_WALKCOMMAND_H
