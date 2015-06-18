//
// Created by root on 15-6-15.
//
#include "PoleCommand.h"
#include "../Gonio.h"

void PoleCommand::init()
{
    this->servoDriver->send(Gonio("paaldansInit.csv").calcVars());
}

void PoleCommand::run()
{
    this->servoDriver->send(Gonio("paaldans.csv").calcVars());
};
