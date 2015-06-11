//
// Created by nieeles van der Boersma on 10-6-2015.
//

#ifndef SPIN_IMOVEMENT_H
#define SPIN_IMOVEMENT_H

#include <vector>
class IMovement {
public:
    // List with 18*x servoPos
    std::vector<int> servoPos;

    virtual void init()=0;
    virtual void move()=0;
};


#endif //SPIN_IMOVEMENT_H
