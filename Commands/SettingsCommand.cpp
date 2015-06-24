//
// Created by root on 23-6-15.
//

#include "SettingsCommand.h"
#include "../Gonio.h"

SettingsCommand::SettingsCommand(ServoDriver *servoDriver, ControlData *controlData) : ICommand(servoDriver,
                                                                                                controlData) {

}

void SettingsCommand::init() {

}

void SettingsCommand::run() {

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

    if (controlData->x < 350 || controlData->x > 650 || controlData->y < 350 || controlData->y > 650) {

        //Calculate the deltas
        dX = (controlData->x <= center) ? center - controlData->x : controlData->x - center;
        dY = (controlData->y <= center) ? center - controlData->y : controlData->y - center;

        if (dX > dY) {
            if (controlData->x > center) {
                this->input = callCSV("turnlInit.csv", "turnl.csv");
            } else {
                this->input = callCSV("turnrInit.csv", "turnr.csv");
            }
        }else // Anders verticaal bewegen
        {
            if (controlData->y > center) {
                this->input = callCSV("moveuInit.csv","moveu.csv");
            } else {
                this->input = callCSV("movedInit.csv","moved.csv");
            }
        }


        servoDriver->sendSyncWrite(this->input, 200000, 300);
        this->lastCSV = this->currCSV;
    }
}

std::vector<std::vector<int>> SettingsCommand::callCSV(std::string initCSV, std::string normalCSV)
{
    std::vector<std::vector<int>> result;

    if(lastCSV != currCSV){
        std::cout << "settomgscommand init: " << initCSV << std::endl;
        result = Gonio(initCSV).calcVars();
        currCSV = initCSV;
    }else{
        std::cout << "settomgscommand run: " << normalCSV << std::endl;
        result = Gonio(normalCSV).calcVars();
        currCSV = normalCSV;
    }

    return result;
}