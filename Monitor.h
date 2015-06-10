//
// Created by eele on 9-6-2015.
//

#ifndef SPIN_MONITOR_H
#define SPIN_MONITOR_H


#include <functional>
#include "SensorData.h"

class Monitor {
public:

    bool filter(); // todo: implement
    SensorData get(); // todo: implement
    void run(std::reference_wrapper<SensorData> sensorData);
};


#endif //SPIN_MONITOR_H
