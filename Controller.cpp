//
// Created by eele on 8-6-2015.
//

#include <iostream>
#include <functional>
#include "Controller.h"

Controller::Controller() {
    state = State::MENU;
    lastState = State::GAP; //Dit doen we om de init aan te roepen bij het opstarten
    bool isRunning = true;

    SensorData sensorData;
    Monitor monitor(std::ref(sensorData));

    ControlData controlData;
    BluetoothHandler bluetoothHandler(std::ref(controlData));

    ServoDriver servoDriver;

    ServerHandler server(std::ref(sensorData));
    WalkCommand walkCommand(&servoDriver);

    std::cout << "Controller started!" << std::endl;

    while (isRunning) {
        switch (state) {

            case State::MENU :
                this->lastState = callCommand(state, lastState, &walkCommand);
                break;

            case State::LIMBO: break;
            case State::GRINDBAK: break;
            case State::RACE: break;
            case State::DANS: break;
            case State::GAP: break;
            case State::PRIK: break;
            case State::PAALDANS: break;
            case State::PAREN: break;

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