//
// Created by root on 15-6-15.
//

#ifndef SPIN_GAPCOMMAND_H
#define SPIN_GAPCOMMAND_H

#include "ICommand.h"

class GapCommand : public ICommand{
public:
    GapCommand(ServoDriver *servoDriver) : ICommand(servoDriver) { }

    virtual void init() override;

    virtual void run() override;
};

#endif //SPIN_GAPCOMMAND_H
