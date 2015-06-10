//
// Created by eele on 10-6-2015.
//

#ifndef SPIN_IMOVEMENT_H
#define SPIN_IMOVEMENT_H

#include <vector>
class IMovement {
private:
    // List with 18*x servoPos
    std::vector<int> servoPos;

    virtual void init();
    virtual void move();
};


#endif //SPIN_IMOVEMENT_H
