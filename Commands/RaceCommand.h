//
// Created by root on 22-6-15.
//

#ifndef SPIN_RACECOMMAND_H
#define SPIN_RACECOMMAND_H


#include "ICommand.h"

class RaceCommand : public ICommand{

public:
    RaceCommand(ServoDriver *servoDriver);

    virtual void init() override;

    virtual void run() override;
};


#endif //SPIN_RACECOMMAND_H
