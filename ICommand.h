//
// Created by eele on 10-6-2015.
//

#ifndef SPIN_ICOMMAND_H
#define SPIN_ICOMMAND_H


#include <vector>
#include <iostream>

class ICommand {
public:
    //std::vector<int> servoPos;

    virtual void init(std::vector<int> vars)=0;

    virtual void run(std::vector<int> vars)=0;
};


#endif //SPIN_ICOMMAND_H