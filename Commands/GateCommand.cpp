//
// Created by root on 15-6-15.
//

#include "GateCommand.h"
#include "../Gonio.h"

void GateCommand::init()
{
        this->servoDriver->send(Gonio("gateInit.csv").calcVars());
}

void GateCommand::run()
{
        this->servoDriver->send(Gonio("gate.csv").calcVars());
};