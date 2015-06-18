//
// Created by root on 15-6-15.
//

#include "BalloonCommand.h"
#include "../Gonio.h"

void BalloonCommand::init()
{
    this->servoDriver->send(Gonio("balloonInit.csv").calcVars());
}

void BalloonCommand::run()
{
    this->servoDriver->send(Gonio("balloon.csv").calcVars());
};