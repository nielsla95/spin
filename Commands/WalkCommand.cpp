//
// Created by eele on 10-6-2015.
//

#include <unistd.h>
#include "WalkCommand.h"
#include "../Gonio.h"

void WalkCommand::init()
{
    // init in voorwaartse loop positie
    this->currCSV = "movefInit.csv";
    this->input = Gonio(currCSV).calcVars();
    servoDriver->sendSyncWrite(this->input,200000,300);
    this->lastCSV = currCSV;
    std::cout << "wc org init 1 : " << currCSV << std::endl;
}

//Im deeply sorry
void WalkCommand::run()
{
    // choose direction

    // knuppels stats
    // knuppel mid(x,y) = 512,512
    // knuppel links = 1023
    // knuppel up = 1023
    // knuppel rechts = 0
    // knuppel down = 0

    // deltaX & delta Y
    int dX = 0;
    int dY = 0;
    int center = 512;

    if(controlData->x<350 || controlData-> x>650 || controlData->y<350 || controlData-> y>650) {

        //Calculate the deltas
        dX = (controlData->x <= center) ? center - controlData->x : controlData->x - center;
        dY = (controlData->y <= center) ? center - controlData->y : controlData->y - center;

        // Zoja horizontaal bewegen
        if (dX > dY) {
            if (controlData->x < center) {
                this->input = callCSV("moverGInit.csv","moverG.csv");
            } else {
                this->input = callCSV("movelInit.csv","movel.csv");
            }
        }
        else // Anders verticaal bewegen
        {
            if (controlData->y > center) {
                this->input = callCSV("movesfInit.csv","movesf.csv");
            } else {
                this->input = callCSV("movesbInit.csv","movesb.csv");
            }
        }

        servoDriver->sendSyncWrite(this->input,200000,300);
        this->lastCSV = this->currCSV;
    }
};

std::vector<std::vector<int>> WalkCommand::callCSV(std::string initCSV, std::string normalCSV)
{
    std::vector<std::vector<int>> result;

    if(lastCSV != currCSV){
        std::cout << "wc init 1 : " << initCSV << std::endl;
        result = Gonio(initCSV).calcVars();
        currCSV = initCSV;
    }else{
        std::cout << "wc run 1 : " << normalCSV << std::endl;
        result = Gonio(normalCSV).calcVars();
        currCSV = normalCSV;
    }

    return result;
}