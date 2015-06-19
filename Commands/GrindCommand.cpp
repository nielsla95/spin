//
// Created by root on 15-6-15.
//

#include "GrindCommand.h"
#include "../Gonio.h"

void GrindCommand::init()
{
    // todo: wegcommenten
    //std::cout << "speed init " << controlData->speed << std::endl;
    servoDriver->send(Gonio("movegInit.csv").calcVars(),controlData->speed,controlData->speed,false);
}

void GrindCommand::run()
{
    //std::cout << "speed run " << controlData->speed << std::endl;
    servoDriver->send(Gonio("moveg.csv").calcVars(),controlData->speed,controlData->speed,false);
};