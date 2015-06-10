//
// Created by eele on 8-6-2015.
//

#ifndef SPIN_CONTROLLER_H
#define SPIN_CONTROLLER_H


#include "Leg.h"
#include "Servo.h"
#include "Monitor.h"
#include "ServerHandler.h"
#include "ICommand.h"
#include "WalkCommand.h"

enum class State {UNDEFINED, WALK, DANCE, POLE, BALLOON};
static const std::string stateNames[5] = {"UNDEFINED",  "WALK", "DANCE", "POLE", "BALLOON" };
enum class MovementState {UNDEFINED, DEFAULT, SMALL, GAP};
static const std::string movementStateNames[4] = {"UNDEFINED", "DEFAULT", "SMALL", "GAP" };

class Controller {
private:

public:
    State state;
    State lastState;
    MovementState movementState;
    MovementState lastMovementState;
    Monitor monitor;
    ServerHandler server;

    // Legs
    Leg leg1;
    Leg leg2;
    Leg leg3;
    Leg leg4;
    Leg leg5;
    Leg leg6;
    Controller();
    State callCommand(State currentState, State lastState, std::reference_wrapper<WalkCommand> command, std::vector<int> vars);

};

#endif //SPIN_CONTROLLER_H