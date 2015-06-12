//
// Created by eele on 8-6-2015.
//

#include <iostream>
#include <functional>
#include "Controller.h"

Controller::Controller() {
    state = State::WALK;
    lastState = State::UNDEFINED;
    bool isRunning = true;

    SensorData sensorData;
    //Monitor monitor(std::ref(sensorData));
    ServerHandler server;
    ControlData controlData;
    BluetoothHandler bluetoothHandler(std::ref(controlData));
    ServoDriver servoDriver;

    WalkCommand walkCommand(&servoDriver);

    std::cout << "Controller started!" << std::endl;

    while (isRunning) {
        switch (state) {
            case State::DANCE:

                break;
            case State::POLE:

                break;
            case State::WALK:
                this->lastState = callCommand(state, lastState, &walkCommand);
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
        // show new state
        std::cout << "State: " << stateNames[(int) state] << std::endl;
    }
    else //The init has been done lets do the run now
    {
        command->run();
    }

    return currentState;
}