//
// Created by root on 15-6-15.
//

#include "DanceCommand.h"
#include "../Gonio.h"

void DanceCommand::init()
{
//    std::vector<std::vector<int>> servoPos =
//            {
//                    {512,640,1016,419,640,1016,512,640,1016,512,383,1016,419,383,1016,512,383,1016}
//            };
//    this->servoDriver->sendMultiple(servoPos);
    this->servoDriver->sendMultiple(Gonio("dansInit.csv").calcVars());
}

void DanceCommand::run()
{
//    std::vector<std::vector<int>> servoPos =
//            {
//                    {512,640,1016,419,702,1022,512,640,1016,512,321,1022,419,383,1016,512,321,1022},
//                    {512,640,1016,419,656,989,512,640,1016,512,367,989,419,383,1016,512,367,989},
//                    {512,702,1022,419,656,989,512,702,1022,512,367,989,419,321,1022,512,367,989},
//                    {512,702,1022,419,650,1003,512,702,1022,512,373,1003,419,321,1022,512,373,1003},
//                    {512,702,1022,419,640,1016,512,702,1022,512,383,1016,419,321,1022,512,383,1016},
//                    {512,656,989,419,640,1016,512,656,989,512,383,1016,419,367,989,512,383,1016}
//            };
//
//    this->servoDriver->sendMultiple(servoPos);
    this->servoDriver->sendMultiple(Gonio("dans.csv").calcVars());
};
