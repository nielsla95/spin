//
// Created by root on 11-6-15.
//

#ifndef SPIN_BLUETOOTHDATA_H
#define SPIN_BLUETOOTHDATA_H


#include "../Controller.h"

class ControlData {

public:
    void set(std::string input) // todo: convert input string to seperated variables
    {

    }
    int x;
    int y;
    int z;
    int speed;
    int mode;
    bool killSwitch; // todo: mode per int aangeven
    bool killRedBalloon; // 0 = kill blue balloon, 1 = kill red balloon
};


#endif //SPIN_BLUETOOTHDATA_H
