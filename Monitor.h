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
    Monitor(std::reference_wrapper<SensorData> sensorData){monitorThread = std::thread(&Monitor::run,this, std::ref(sensorData)); };

    virtual ~Monitor() { monitorThread.join(); }

    bool filter(); // todo: implement
    SensorData get(); // todo: implement
    void run(std::reference_wrapper<SensorData> sensorData);
};


#endif //SPIN_MONITOR_H
