//
// Created by root on 15-6-15.
//

#include "GateCommand.h"
#include "../Gonio.h"

void GateCommand::init()
{
        this->servoDriver->sendMultiple(Gonio("gateInit.csv").calcVars());
}

void GateCommand::run()
{
        this->servoDriver->sendMultiple(Gonio("gate.csv").calcVars());
};