//
// Created by root on 15-6-15.
//

#include "BalloonCommand.h"
#include "../Gonio.h"

void BalloonCommand::init()
{
    servoDriver->send(Gonio("movesfInit.csv").calcVars(),200,100,true);
}

void BalloonCommand::run()
{
    servoDriver->send(Gonio("movesf.csv").calcVars(),200,100,true);
};