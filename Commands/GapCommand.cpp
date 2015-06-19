//
// Created by root on 15-6-15.
//

#include "GapCommand.h"
#include "../Gonio.h"

void GapCommand::init()
{
    this->servoDriver->send(Gonio("moverInit.csv").calcVars(),1023,500,true);
}

void GapCommand::run()
{
    this->servoDriver->send(Gonio("mover.csv").calcVars(),1023,500,true);
};
