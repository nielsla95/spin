//
// Created by root on 15-6-15.
//

#include "DanceCommand.h"
#include "../Gonio.h"

void DanceCommand::init()
{
    this->servoDriver->send(Gonio("turnlInit.csv").calcVars(),1023,500,true);
}

void DanceCommand::run()
{
    this->servoDriver->send(Gonio("turnl.csv").calcVars(),1023,500,true);
};
