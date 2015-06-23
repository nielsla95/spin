//
// Created by root on 15-6-15.
//
#include "PoleCommand.h"
#include "../Gonio.h"

void PoleCommand::init()
{
    std::cout << "INIT PAAL" << std::endl;
}

void PoleCommand::run()
{
    // todo: PERFECT RONDJE tetsen
    for (int i = 0; i < 29; ++i) {
        //std::cout << "Afstand paal: " << sensorData->dist << std::endl;

        this->servoDriver->sendSyncWrite(Gonio("moverGInit.csv").calcVars(),100000,200);
        this->servoDriver->sendSyncWrite(Gonio("moverG.csv").calcVars(),100000,200);
        this->servoDriver->sendSyncWrite(Gonio("moverG.csv").calcVars(),100000,200);
        this->servoDriver->sendSyncWrite(Gonio("turnlInit.csv").calcVars(),150000,200);
        this->servoDriver->sendSyncWrite(Gonio("turnl.csv").calcVars(),150000,200);
        if(this->sensorData->dist < (25 - 10))//NOG TE DOOEEEEN
        {

        }
        else if(this->sensorData->dist > (25 + 10))
        {

        }
        std::cout << "Rondje counter: " << i << std::endl;
    }

};
