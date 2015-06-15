//
// Created by eele on 8-6-2015.
//

#include <iostream>
#include <functional>
#include "Controller.h"

Controller::Controller() {
    state = State::WALK_SMALL;
    lastState = State::UNDEFINED;
    bool isRunning = true;

    SensorData sensorData;
    //Monitor monitor(std::ref(sensorData));
    ServerHandler server;
    ControlData controlData;
    //BluetoothHandler bluetoothHandler(std::ref(controlData));
    ServoDriver servoDriver;
    servoDriver.init();

    WalkCommand walkCommand(&servoDriver);
    PoleCommand poleCommand(&servoDriver);
    GateCommand gateCommand(&servoDriver);
    DanceCommand danceCommand(&servoDriver);
    BalloonCommand balloonCommand(&servoDriver);
    GapCommand gapCommand(&servoDriver);

    std::cout << "Controller started!" << std::endl;

    while (isRunning) {
        switch (state) {
            case State::DANCE:
                this->lastState = callCommand(state, lastState, &danceCommand);
                break;
            case State::POLE:
                this->lastState = callCommand(state, lastState, &poleCommand);
                break;
            case State::WALK:
                this->lastState = callCommand(state, lastState, &walkCommand);
                break;
            case State::WALK_SMALL:
                this->lastState = callCommand(state, lastState, &gateCommand);
                break;
            case State::BALLOON:
                this->lastState = callCommand(state, lastState, &balloonCommand);
                break;
            case State::GAP:
                this->lastState = callCommand(state, lastState, &gapCommand);
                break;
            default:
                std::cout << "U r a wizzart, how u get here? Bud how you leave here!??" << std::endl;
                break;
        }
    }
}

State Controller::callCommand(State currentState, State lastState, ICommand *command)
{

    //Call the init for the current state
    if(currentState != lastState)
    {
        command->init();
        std::cout << "init exit";
        // show new state
        std::cout << "State: " << stateNames[(int) state] << std::endl;
    }
    else //The init has been done lets do the run now
    {
        command->run();
    }

    return currentState;
}