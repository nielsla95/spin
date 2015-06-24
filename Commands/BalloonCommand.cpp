//
// Created by root on 15-6-15.
//

#include <unistd.h>
#include "BalloonCommand.h"
#include "../Gonio.h"

void BalloonCommand::init()
{
    std::cout <<  "begin" << std::endl;
    bool hasPrikked=false;

    // TODO FIXEN
    if(*balloon!=0){
        std::cout << "werkt nog" << std::endl;
        while(!hasPrikked){
            std::cout << "Test x: " << *x << std::endl;
            std::cout << "Test y: " << *y << std::endl;
            //6
            usleep(200000);
            //320 x 240

            if(*x >= ((320 /2) + 20)){
                //std::cout << "ballon bevind zich rechts, draaien" << std::endl;
                servoDriver->sendSyncWrite(Gonio("turnrInit.csv").calcVars(),200000,300);
                servoDriver->sendSyncWrite(Gonio("turnr.csv").calcVars(),200000,300);
            }
            std::cout << "ballon bevind zich niet rechts" << std::endl;
            if((*x <= (320 / 2)-20 && *x > 0 )  ){
                //std::cout << "ballon bevind zich links, draaien." << std::endl;
                servoDriver->sendSyncWrite(Gonio("turnlInit.csv").calcVars(),200000,300);
                servoDriver->sendSyncWrite(Gonio("turnl.csv").calcVars(),200000,300);
            }
            if(*x >= (320 / 2)-20 && *x <= (320 / 2) + 20 )
            {
                //std::cout << "ballon bevind zich in het midden, rechtdoor lopen." << std::endl;
                std::cout << "afstand tot het object is: " << this->sensorData->dist << "." << std::endl;
                if(this->sensorData->dist <= 20)
                {
                    std::cout << "afstand tot het object is(ikwilprikken): " << this->sensorData->dist << "." << std::endl;
                    //servoDriver->sendSyncWrite(Gonio("movesfInit.csv").calcVars(), 165000,300);//verander naar achteruit lopen
                    //servoDriver->sendSyncWrite(Gonio("movesf.csv").calcVars(), 165000,300);
                    this->prik();
                    hasPrikked = true;
                }
                else
                {
                    servoDriver->sendSyncWrite(Gonio("movesfInit.csv").calcVars(), 165000,300);
                    servoDriver->sendSyncWrite(Gonio("movesf.csv").calcVars(), 165000,300);
                }

            }
            if(*x == 0){
                //std::cout << "kan niks zien" << std::endl;
                servoDriver->sendSyncWrite(Gonio("turnlInit.csv").calcVars(),200000,300);
                servoDriver->sendSyncWrite(Gonio("turnl.csv").calcVars(),200000,300);
            }
        }
    }
}

void BalloonCommand::run()
{

};

void BalloonCommand::prik() {
    std::vector<std::vector<int>> prikInit{
            {512,691,1002,419,703,1006,512,703,1006,512,320,1006,419,320,1006,512,332,1002},
            {512,766,952,419,766,952,512,766,952,512,257,952,419,257,952,512,257,952}
    };

    this->servoDriver->sendSyncWrite(prikInit,2000000,100);

    // prik run
    std::vector<std::vector<int>> prik{
            {519,749,726,419,766,952,512,766,952,512,257,952,419,257,952,514,280,732},
            {236,771,727,419,766,952,512,766,952,512,257,952,419,257,952,801,255,732},
            {512,766,952,419,766,952,512,766,952,512,257,952,419,257,952,512,257,952},
            {512,691,1002,419,703,1006,512,703,1006,512,320,1006,419,320,1006,512,332,1002}
    };

    this->servoDriver->sendSyncWrite(prik,200000,500);
}
