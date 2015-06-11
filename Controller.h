//
// Created by eele on 8-6-2015.
//

#ifndef SPIN_CONTROLLER_H
#define SPIN_CONTROLLER_H


#include "Models/Servo.h"
#include "Monitor.h"
#include "ServerHandler.h"
#include "Commands/ICommand.h"
#include "Commands/WalkCommand.h"
#include "Models/Leg.h"
#include "ServoDriver.h"
#include "BluetoothHandler.h"

enum class State {UNDEFINED, WALK, WALK_SMALL, DANCE, POLE, BALLOON, GAP};

static const std::string stateNames[7] = {"UNDEFINED", "WALK", "WALK_SMALL","DANCE", "POLE", "BALLOON", "GAP" };

class Controller {
private:

public:
    State state;
    State lastState;

    Controller();
    State callCommand(State currentState, State lastState, ICommand *command);
};

#endif //SPIN_CONTROLLER_H