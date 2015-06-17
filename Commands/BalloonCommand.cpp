//
// Created by root on 15-6-15.
//

#include "BalloonCommand.h"
#include "../Gonio.h"

void BalloonCommand::init()
{
    this->servoDriver->sendMultiple(Gonio("balloonInit.csv").calcVars());
}

void BalloonCommand::run()
{
    this->servoDriver->sendMultiple(Gonio("balloon.csv").calcVars());
};