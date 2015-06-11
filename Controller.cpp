//
// Created by eele on 8-6-2015.
//

#include <iostream>
#include <functional>
#include "Controller.h"
#include <thread>

void aids(void){
    std::cout << " aids"  << std::endl;
}
Controller::Controller() {
    state = State::WALK;
    lastState = State::UNDEFINED;
    bool isRunning = true;
    std::vector<int> test;
    WalkCommand walkCommand;
    DefaultMovement defaultMovement;

    SensorData sensorData;
    //Monitor monitor(std::ref(sensorData));
    ServerHandler server;
    BluetoothHandler bluetoothHandler;
    ServoDriver servoDriver;

//    leg1 = Leg(inits[0],inits[1],inits[2]);
//    leg2 = Leg(inits[3],inits[4],inits[5]);
//    leg3 = Leg(inits[6],inits[7],inits[8]);
//    leg4 = Leg(inits[9],inits[10],inits[11]);
//    leg5 = Leg(inits[12],inits[13],inits[14]);
//    leg6 = Leg(inits[15],inits[16],inits[17]);

    std::cout << "Controller started!" << std::endl;

    while (isRunning) {
        std::cout << "MonitorData test: " << sensorData.test << std::endl;
        switch (state) {
            case State::DANCE:

                break;
            case State::POLE:

                break;
            case State::WALK:
                this->lastState = callCommand(state, lastState, &walkCommand,test);
                break;
            default:
                std::cout << "U r a wizzart, how u get here? Bud how you leave here!??" << std::endl;
                break;
        }
    }
}

State Controller::callCommand(State currentState, State lastState, ICommand *command, std::vector<int> vars)
{

    //Call the init for the current state
    if(currentState != lastState)
    {
        command->init(vars);
        // show new state
        std::cout << "State: " << stateNames[(int) state] << std::endl;
    }
    else //The init has been done lets do the run now
    {
        command->run(vars);
    }

    return currentState;
}