//
// Created by eele on 10-6-2015.
//

#ifndef SPIN_DEFAULTMOVEMENT_H
#define SPIN_DEFAULTMOVEMENT_H


#include <iostream>
#include "IMovement.h"

class DefaultMovement : public IMovement{
public:
    virtual void init() override;

    virtual void move() override;
};


#endif //SPIN_DEFAULTMOVEMENT_H
