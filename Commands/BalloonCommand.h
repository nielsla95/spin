//
// Created by root on 15-6-15.
//

#ifndef SPIN_BALLOONCOMMAND_H
#define SPIN_BALLOONCOMMAND_H

#include "ICommand.h"

class BalloonCommand : public ICommand{
public:
    BalloonCommand(ServoDriver *servoDriver) : ICommand(servoDriver) { }

    virtual void init() override;

    virtual void run() override;
};


#endif //SPIN_BALLOONCOMMAND_H
