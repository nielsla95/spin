//
// Created by eele on 8-6-2015.
//

#include <iostream>
#include <functional>
#include "Controller.h"
#include "Gonio.h"

Controller::Controller() {
    ControlData controlData;
    state = State::MENU;
    lastState = State::DANS; //Dit doen we om de init aan te roepen bij het opstarten
    bool isRunning = true;
    Gonio gon("vooruit.csv");

    SensorData sensorData;
    Monitor monitor(std::ref(sensorData));


    BluetoothHandler bluetoothHandler(std::ref(controlData));

    ServoDriver servoDriver;
    servoDriver.init();

    ServerHandler server(std::ref(sensorData),std::ref(controlData));
    WalkCommand walkCommand(&servoDriver);
    PoleCommand poleCommand(&servoDriver);
    GapCommand gapCommand(&servoDriver);

    std::cout << "Controller started!" << std::endl;

    while (isRunning) {
        switch (state) {
	    case State::MENU:
                this->lastState = callCommand(state, lastState, &walkCommand);
                break;

            case State::LIMBO: break;
            case State::GRINDBAK: break;
            case State::RACE: break;
            case State::DANS: break;
            case State::GAP: 
		this->lastState = callCommand(state, lastState, &gapCommand);
		break;
            case State::PRIK: break;
            case State::PAALDANS:
		this->lastState = callCommand(state, lastState, &poleCommand);
		break;
            case State::PAREN: break;

            default:
                std::cout << "U r a wizzart, how u get here? Bud how you leave here!??" << std::endl;
                break;
        }
    }
}

State Controller::callCommand(State currentState, State lastState, ICommand *command)
{
    std::cout <<"callCommand" << std::endl;
    //Call the init for the current state
    if(currentState != lastState)
    {
        command->init();
        // show new state
        std::cout << "State: " << stateNames[(int) state] << std::endl;
	printf("Init state ding");
    }
    else //The init has been done lets do the run now
    {
	std::cout << "Not init" << std::endl;
	printf("not init");
        command->run();
    }

    return currentState;
}
