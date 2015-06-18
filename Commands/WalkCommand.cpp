//
// Created by eele on 10-6-2015.
//

#include "WalkCommand.h"
#include "../Gonio.h"

void WalkCommand::init()
{
    currCSV = "vooruitlopenpoortjeInit.csv";
    servoDriver->send(Gonio(currCSV).calcVars());
}

//Im deeply sorry
void WalkCommand::run()
{

    // choose direction

    // links rechts
    if(abs(controlData->x) > abs(controlData->y))
    {
        if(controlData->x > 0){
            if(lastCSV != "moverInit"){
                std::vector<std::vector<int>> input = Gonio("moverInit.csv").calcVars();
                currCSV = "moverInit";
            }
            else
            {
                std::vector<std::vector<int>> input = Gonio("mover.csv").calcVars();
                currCSV = "mover";
            }
        }else{
            if(lastCSV != "movelInit")
            {
                std::vector<std::vector<int>> input = Gonio("movelInit.csv").calcVars();
                currCSV = "movelInit";
            }
            else
            {
                std::vector<std::vector<int>> input = Gonio("movel.csv").calcVars();
                currCSV = "movel";
            }
        }
    }
    else // vooruit achteruit
    {
        if(controlData->y > 0){
            if(lastCSV != "movefInit"){
                std::vector<std::vector<int>> input = Gonio("movefInit.csv").calcVars();
                currCSV = "movefInit";
            }
            else
            {
                std::vector<std::vector<int>> input = Gonio("movef.csv").calcVars();
                currCSV = "movef";
            }

        }else{
            if(lastCSV != "movebInit"){
                std::vector<std::vector<int>> input = Gonio("movebInit.csv").calcVars();
                currCSV = "movebInit";
            }
            else
            {
                std::vector<std::vector<int>> input = Gonio("moveb.csv").calcVars();
                currCSV = "moveb";
            }

        }
    }

    std::vector<std::vector<int>> input = Gonio("vooruitlopenpoortje.csv").calcVars();

    this->servoDriver->send(input);

    lastCSV = currCSV;
};

