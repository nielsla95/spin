//
// Created by eele on 8-6-2015.
//

#include <iostream>
#include <functional>
#include "Controller.h"
#include "Gonio.h"
#include "Commands/GrindCommand.h"

Controller::Controller() {
    ControlData controlData;
    controlData.set(512,512,512,100,1,false,0);
    ControlData lastControlData;
    lastControlData.set(512,512,512,100,1,false,0);
    state = State::MENU;
    lastState = State::GRINDBAK; //Dit doen we om de init aan te roepen bij het opstarten
    bool isRunning = true;

    SensorData sensorData;
    Monitor monitor(std::ref(sensorData));

    int visionX = 0;//				vision
    int visionY = 0;//				vision

    BluetoothHandler bluetoothHandler(std::ref(controlData));
    //Vision vis(&visionX,&visionY); //	vision

    ServoDriver servoDriver;

    //ServerHandler server(std::ref(sensorData),std::ref(controlData));
    WalkCommand walkCommand(&servoDriver, &controlData);
    PoleCommand poleCommand(&servoDriver);
    GapCommand gapCommand(&servoDriver);
    GrindCommand grindCommand(&servoDriver, &controlData);
    BalloonCommand balloonCommand(&servoDriver);
    DanceCommand danceCommand(&servoDriver);

    while (isRunning) {
        isRunning = !controlData.killSwitch;
        // CUSTOM CONTROL //

        std::cout << "VOER JE MODER IN: " << std::endl;
        int newState;
        std::cin >> newState;
        state = (State)newState;

        // END CUSTOM CONTROL //

        ///////////////////////
        // BLUETOOTH CONTROL //
//
//        if((controlData.isNotEqual(lastControlData))){
//            state = (State)controlData.mode;
//            lastControlData = controlData;
//        }

        // END BLUETOOTH CONTROL//
        //////////////////////////

        switch (state) {
	        case State::MENU:
                this->lastState = callCommand(&walkCommand);
                break;
            case State::LIMBO:
                this->lastState = callCommand(&danceCommand);
                break;
            case State::GRINDBAK:
                this->lastState = callCommand(&grindCommand);
                break;
            case State::RACE:
                this->lastState = callCommand(&danceCommand);
                break;
            case State::DANS:
                this->lastState = callCommand(&danceCommand);
                break;
            case State::GAP: 
		        this->lastState = callCommand(&gapCommand);
		        break;
            case State::PRIK:
                this->lastState = callCommand(&balloonCommand);
                break;
            case State::PAALDANS:
		        this->lastState = callCommand(&poleCommand);
		        break;
            case State::PAREN:
                this->lastState = callCommand(&danceCommand);
                break;

            default:
                std::cout << "U r a wizzart, how u get here? Bud how you leave here!??" << std::endl;
                break;
        }
    }
}

State Controller::callCommand(ICommand *command)
{
    //Call the init for the current state
    if(state != lastState)
    {
        //std::cout << "Init - state: " << stateNames[(int) state] << std::endl;
        command->init();
    }
    else //The init has been done lets do the run now
    {
	    //std::cout << "Running - state: " << stateNames[(int) state] << std::endl;
        command->run();
    }
    // todo: sleep weghalen
    //usleep(2000000);
    return state;
}
