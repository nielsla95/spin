//
// Created by root on 15-6-15.
//

#ifndef SPIN_BALLOONCOMMAND_H
#define SPIN_BALLOONCOMMAND_H

#include "ICommand.h"

class BalloonCommand : public ICommand{
public:


    BalloonCommand(ServoDriver *servoDriver, SensorData *sensorData, int *x, int *y) : ICommand(servoDriver, sensorData,
                                                                                                x, y) { }

    virtual void init() override;

    virtual void run() override;

    void prik();
};


#endif //SPIN_BALLOONCOMMAND_H
