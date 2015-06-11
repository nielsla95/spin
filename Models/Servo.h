//
// Created by niels on 8-6-15.
//

#ifndef SPIN_SERVO_H
#define SPIN_SERVO_H

#include <iostream>

class Servo {

private:
    int id;
    int temp;
    int degree;
public:
    Servo() {}
    Servo(int id, int temp, int degree) : id(id), temp(temp), degree(degree) {}

    int getId() const {
        return id;
    }

    void setId(int id) {
        Servo::id = id;
    }

    int getDegree() const {
        return degree;
    }

    void setDegree(int degree) {
        Servo::degree = degree;
    }

    int getTemp() const {
        return temp;
    }

    void setTemp(int temp) {
        Servo::temp = temp;
    }
};


#endif //SPIN_SERVO_H
