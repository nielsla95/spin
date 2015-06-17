//
// Created by eele on 10-6-2015.
//

#include "WalkCommand.h"
#include "../Gonio.h"

void WalkCommand::init()
{
    this->servoDriver->sendMultiple(Gonio("vooruitlopenpoortjeInit.csv").calcVars());
}

void WalkCommand::run()
{
    std::vector<std::vector<int>> input = Gonio("vooruitlopenpoortje.csv").calcVars();

    for (int i = 0; i < 4; ++i) {
        this->servoDriver->sendMultiple(input);
    }

};

