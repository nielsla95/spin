//
// Created by eele on 9-6-2015.
//

#include <iostream>
#include <unistd.h>
#include "Monitor.h"

void Monitor::run(std::reference_wrapper<SensorData> sensorData)
{
    while(true)
    {
        sensorData.get().setTest(rand());
        sleep(2);
    }
}