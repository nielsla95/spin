//
// Created by root on 15-6-15.
//

#include "DanceCommand.h"
#include "../Gonio.h"

void DanceCommand::init()
{
    this->servoDriver->sendSyncWrite(Gonio("test.csv").calcVars(),100);
}

void DanceCommand::run()
{
    this->servoDriver->sendSyncWrite(Gonio("test.csv").calcVars(),100);
};
