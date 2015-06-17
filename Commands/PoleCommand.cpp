//
// Created by root on 15-6-15.
//
#include "PoleCommand.h"
#include "../Gonio.h"

void PoleCommand::init()
{
    this->servoDriver->sendMultiple(Gonio("zijwaardsInit.csv").calcVars());
}

void PoleCommand::run()
{
    this->servoDriver->sendMultiple(Gonio("zijwaards.csv").calcVars());
};
