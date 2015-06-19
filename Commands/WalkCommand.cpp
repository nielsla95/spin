//
// Created by eele on 10-6-2015.
//

#include <unistd.h>
#include "WalkCommand.h"
#include "../Gonio.h"

void WalkCommand::init()
{
    // todo: wegcommenten

    currCSV = "movelInit.csv";
    servoDriver->send(Gonio(currCSV).calcVars(),200,100,true);
    lastCSV = currCSV;
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
    //

    int dX = 0;
    int dY = 0;
    //std::cout << "X: " << controlData->x << std::endl;
    //std::cout << "Y: " << controlData->y << std::endl;

    if(controlData->x<350 || controlData-> x>650 || controlData->y<350 || controlData-> y>650) {
        // kijk verschil x met xmid=512
        if (controlData->x <= 512)
            dX = 512 - controlData->x;
        else dX = controlData->x - 512;

        if (controlData->y <= 512)
            dY = 512 - controlData->y;
        else
            dY = controlData->y - 512;

        // kijk verschil y met ymid=512
        if (dX > dY) {
            std::cout << "IK BEWEEG X" << std::endl;
            if (controlData->x < 512) {
                if (lastCSV != "moverInit.csv") {
                    std::cout << "IK BEWEEG X - moverInit " << controlData->x << std::endl;
                    std::vector<std::vector<int>> input = Gonio("moverInit.csv").calcVars();
                    currCSV = "moverInit.csv";
                }
                else {
                    std::cout << "IK BEWEEG X - mover " << controlData->x << std::endl;
                    std::vector<std::vector<int>> input = Gonio("mover.csv").calcVars();
                    currCSV = "mover.csv";
                }
            } else {
                if (lastCSV != "movelInit.csv") {
                    std::cout << "IK BEWEEG X - movelInit " << controlData->x << std::endl;
                    std::vector<std::vector<int>> input = Gonio("movelInit.csv").calcVars();
                    currCSV = "movelInit.csv";
                }
                else {
                    std::cout << "IK BEWEEG X - movel " << controlData->x << std::endl;
                    std::vector<std::vector<int>> input = Gonio("movel.csv").calcVars();
                    currCSV = "movel.csv";
                }
            }
        }
        else // vooruit achteruit
        {
            if (controlData->y > 512) {
                std::cout << "IK BEWEEG Y" << std::endl;
                if (lastCSV != "movefInit.csv") {
                    std::cout << "IK BEWEEG Y - movefInit " << controlData->y << std::endl;
                    std::vector<std::vector<int>> input = Gonio("movefInit.csv").calcVars();
                    currCSV = "movefInit.csv";
                }
                else {
                    std::cout << "IK BEWEEG Y - movef " << controlData->y << std::endl;
                    std::vector<std::vector<int>> input = Gonio("movef.csv").calcVars();
                    currCSV = "movef.csv";
                }

            } else {
                if (lastCSV != "movebInit.csv") {
                    std::cout << "IK BEWEEG Y - movebInit " << controlData->y << std::endl;
                    std::vector<std::vector<int>> input = Gonio("movebInit.csv").calcVars();
                    currCSV = "movebInit.csv";
                }
                else {
                    std::cout << "IK BEWEEG Y - moveb " << controlData->y << std::endl;
                    std::vector<std::vector<int>> input = Gonio("moveb.csv").calcVars();
                    currCSV = "moveb.csv";
                }
            }
        }
        servoDriver->send(Gonio(currCSV).calcVars(),200,100,true);
        lastCSV = currCSV;
    }
};

