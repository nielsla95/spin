//
// Created by root on 15-6-15.
//
#include "PoleCommand.h"
#include "../Gonio.h"

void PoleCommand::init()
{
//    std::cout << "POLE INIT" << std::endl;
//    std::vector<std::vector<int>> servoPos =
//            {
//                    {512,576,980,419,576,980,512,576,980,512,447,980,419,447,980,512,447,980}
//            };
//    this->servoDriver->sendMultiple(servoPos);
    this->servoDriver->sendMultiple(Gonio("poleInit.csv").calcVars());
}

void PoleCommand::run()
{
    std::cout << "POLE RUN" << std::endl;
//    std::vector<std::vector<int>> servoPos =
//            {
//                    {512,716,1013,419,576,980,512,716,1013,512,447,980,419,307,1013,512,447,980},
//                    {512,604,936,419,576,980,512,604,936,512,447,980,419,419,936,512,447,980},
//                    {512,604,936,419,716,1013,512,604,936,512,307,1013,419,419,936,512,307,1013},
//                    {512,595,960,419,716,1013,512,595,960,512,307,1013,419,428,960,512,307,1013},
//                    {512,604,936,419,716,1013,512,604,936,512,307,1013,419,419,936,512,307,1013},
//                    {512,604,936,419,604,936,512,604,936,512,419,936,419,419,936,512,419,936}
//
//            };
//
//    this->servoDriver->sendMultiple(servoPos);
    this->servoDriver->sendMultiple(Gonio("pole.csv").calcVars());
};
