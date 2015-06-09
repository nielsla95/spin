//
// Created by eele on 8-6-2015.
//

#ifndef SPIN_LEG_H
#define SPIN_LEG_H


#include "Servo.h"

class Leg {
Servo coxa;
Servo femur;
Servo tibia;
public:


    Leg() { }

    Leg(const Servo &coxa, const Servo &femur, const Servo &tibia) : coxa(coxa), femur(femur), tibia(tibia) {}

    const Servo &getCoxa() const {
        return coxa;
    }

    void setCoxa(const Servo &coxa) {
        Leg::coxa = coxa;
    }

    const Servo &getFemur() const {
        return femur;
    }

    void setFemur(const Servo &femur) {
        Leg::femur = femur;
    }

    const Servo &getTibia() const {
        return tibia;
    }

    void setTibia(const Servo &tibia) {
        Leg::tibia = tibia;
    }
};


#endif //SPIN_LEG_H
