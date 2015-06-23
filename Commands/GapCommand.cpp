//
// Created by root on 15-6-15.
//

#include "GapCommand.h"
#include "../Gonio.h"

void GapCommand::init()
{
    this->servoDriver->sendSyncWrite(Gonio("moverGInit.csv").calcVars(),100000,200);
}

void GapCommand::run()
{
    this->servoDriver->sendSyncWrite(Gonio("moverG.csv").calcVars(),100000,200);
};
