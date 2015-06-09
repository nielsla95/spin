//
// Created by eele on 8-6-2015.
//

#include <iostream>
#include "Controller.h"

enum class State {WALK, DANCE, POLE};
enum class MovementState {DEFAULT, SMALL, GAP};

Controller::Controller(){
    Servo inits[18] = {
            Servo(1,0,512),
            Servo(2,0,512),
            Servo(3,0,512),
            Servo(4,0,512),
            Servo(5,0,512),
            Servo(6,0,512),
            Servo(7,0,512),
            Servo(8,0,512),
            Servo(9,0,512),
            Servo(10,0,512),
            Servo(11,0,512),
            Servo(12,0,512),
            Servo(13,0,512),
            Servo(14,0,512),
            Servo(15,0,512),
            Servo(16,0,512),
            Servo(17,0,512),
            Servo(18,0,512)
    };
    leg1 = Leg(inits[0],inits[1],inits[2]);
    leg2 = Leg(inits[3],inits[4],inits[5]);
    leg3 = Leg(inits[6],inits[7],inits[8]);
    leg4 = Leg(inits[9],inits[10],inits[11]);
    leg5 = Leg(inits[12],inits[13],inits[14]);
    leg6 = Leg(inits[15],inits[16],inits[17]);

    std::cout << "Controller started! hurhur" << std::endl;
}