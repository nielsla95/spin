//
// Created by eele on 8-6-2015.
//

#include <iostream>
#include <functional>
#include "Controller.h"
#include "Gonio.h"
#include "Commands/GrindCommand.h"
#include "Commands/LimboCommand.h"
#include "Commands/RaceCommand.h"
#include "Commands/SettingsCommand.h"

Controller::Controller() {
    ControlData controlData;
    controlData.set(512,512,512,100,1,false,0);
    ControlData lastControlData;
    lastControlData.set(512,512,512,100,1,false,0);
    bool interrupted = false;
    state = State::MENU;
    lastState = State::GRINDBAK; //Dit doen we om de init aan te roepen bij het opstarten
    bool isRunning = true;

    std::vector<int> servoData;
    for(int i = 0; i < 18*3; i++)
        servoData.push_back(0);

    SensorData sensorData;
    Monitor monitor(std::ref(sensorData));

    int visionX = 0;//				vision
    int visionY = 0;//				vision

    BluetoothHandler bluetoothHandler(std::ref(controlData));
    Vision vis(&visionX,&visionY,&controlData.balloon); //	vision

    ServoDriver servoDriver(&servoData);

    ServerHandler server(&sensorData,&controlData,&servoData);

    WalkCommand walkCommand(&servoDriver, &controlData);
    PoleCommand poleCommand(&servoDriver, &sensorData);
    GapCommand gapCommand(&servoDriver);
    GrindCommand grindCommand(&servoDriver, &controlData);
    BalloonCommand balloonCommand(&servoDriver,&sensorData,&visionX,&visionY,&controlData.balloon);
    DanceCommand danceCommand(&servoDriver);
    LimboCommand limboCommand(&servoDriver);
    RaceCommand raceCommand(&servoDriver);
    SettingsCommand settingsCommand(&servoDriver, &controlData);

    std::cout << "init servo data length: " << servoData.size() << std::endl;
    std::cout << "init servo data pointer: " << &servoData << std::endl;

    while (isRunning) {
        //isRunning = !controlData.killSwitch;
        // CUSTOM CONTROL //

        std::cout << "VOER JE MODER IN: " << std::endl;
        int newState;
        std::cin >> newState;
        state = (State)newState;

        // END CUSTOM CONTROL //

        ///////////////////////
        // BLUETOOTH CONTROL //

//        if((controlData.isNotEqual(lastControlData))){
//            state = (State)controlData.mode;
//            lastControlData = controlData;
//        }

        // END BLUETOOTH CONTROL//
        //////////////////////////

        switch (state) {
	        case State::MENU: // 0
                this->lastState = callCommand(&walkCommand);
                break;
            case State::LIMBO: //1
                this->lastState = callCommand(&limboCommand);
                break;
            case State::GRINDBAK: // 2
                this->lastState = callCommand(&grindCommand);
                break;
            case State::RACE: // 3
                this->lastState = callCommand(&raceCommand);
                break;
            case State::DANS: // 4
                this->lastState = callCommand(&danceCommand);
                break;
            case State::GAP: // 5
		        this->lastState = callCommand(&gapCommand);
		        break;
            case State::PRIK: // 6
                this->lastState = callCommand(&balloonCommand);
                break;
            case State::PAALDANS: // 7
		        this->lastState = callCommand(&poleCommand);
		        break;
            case State::PAREN: // 8
                this->lastState = callCommand(&walkCommand);
                break;
            case State::SETTINGS: // 9
                this->lastState = callCommand(&settingsCommand);
                break;
            default:
                std::cout << "U r a wizzart, how u get here? Bud how you leave here!??" << std::endl;
                break;
        }
    }
    std::cout << "KILLSWITCH OH NOES" << std::endl;
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
    return state;
}
