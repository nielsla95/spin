//
// Created by eele on 8-6-2015.
//

#ifndef SPIN_CONTROLLER_H
#define SPIN_CONTROLLER_H


#include "Leg.h"
#include "Servo.h"
class Controller {
private:

public:
    // Legs
    Leg leg1;
    Leg leg2;
    Leg leg3;
    Leg leg4;
    Leg leg5;
    Leg leg6;
    Controller();
};

#endif //SPIN_CONTROLLER_H