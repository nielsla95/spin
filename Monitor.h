//
// Created by eele on 9-6-2015.
//

#ifndef SPIN_MONITOR_H
#define SPIN_MONITOR_H


#include <functional>
#include "Models/SensorData.h"
#include <thread>

class Monitor {
public:
    std::thread monitorThread;
    Monitor(SensorData &sensorData){
        monitorThread = std::thread(&Monitor::listen,this, std::ref(sensorData));
        sensorData.set("<1,2,3,4,5,6>");
    };

    virtual ~Monitor() { monitorThread.join(); }

    void listen(SensorData &sensorData);
};


#endif //SPIN_MONITOR_H
