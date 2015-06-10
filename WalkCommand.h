//
// Created by eele on 10-6-2015.
//

#ifndef SPIN_WALKCOMMAND_H
#define SPIN_WALKCOMMAND_H


#include "ICommand.h"

class WalkCommand : public ICommand{
public:

    virtual void init(std::vector<int> vars) override;

    virtual void run(std::vector<int> vars) override;
};


#endif //SPIN_WALKCOMMAND_H
