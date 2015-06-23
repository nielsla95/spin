//
// Created by root on 22-6-15.
//

#ifndef SPIN_LIMBOCOMMAND_H
#define SPIN_LIMBOCOMMAND_H


#include "ICommand.h"

class LimboCommand : public ICommand {


public:
    LimboCommand(ServoDriver *servoDriver);

    virtual void init() override;

    virtual void run() override;
};


#endif //SPIN_LIMBOCOMMAND_H
