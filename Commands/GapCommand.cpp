//
// Created by root on 15-6-15.
//

#include "GapCommand.h"
#include "../Gonio.h"

void GapCommand::init()
{
    this->servoDriver->send(Gonio("gapInit.csv").calcVars());
}

void GapCommand::run()
{
    this->servoDriver->send(Gonio("gap.csv").calcVars());
};
