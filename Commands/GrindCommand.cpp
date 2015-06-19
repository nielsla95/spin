//
// Created by root on 15-6-15.
//

#include "GrindCommand.h"
#include "../Gonio.h"

void GrindCommand::init()
{
    servoDriver->send(Gonio("movegInit.csv").calcVars(),1023,1023,false);
}

void GrindCommand::run()
{
        servoDriver->send(Gonio("moveg.csv").calcVars(),1023,1023,false);
};