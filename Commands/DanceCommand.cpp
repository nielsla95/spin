//
// Created by root on 15-6-15.
//

#include "DanceCommand.h"
#include "../Gonio.h"

void DanceCommand::init()
{
    this->servoDriver->send(Gonio("dansInit.csv").calcVars());
}

void DanceCommand::run()
{
    this->servoDriver->send(Gonio("dans.csv").calcVars());
};
