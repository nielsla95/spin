//
// Created by root on 15-6-15.
//

#ifndef SPIN_DANCECOMMAND_H
#define SPIN_DANCECOMMAND_H

#include "ICommand.h"

class DanceCommand : public ICommand{
public:
    DanceCommand(ServoDriver *servoDriver) : ICommand(servoDriver) { }

    virtual void init() override;

    virtual void run() override;
};

#endif //SPIN_DANCECOMMAND_H
