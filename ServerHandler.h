//
// Created by eele on 9-6-2015.
//

#ifndef SPIN_SERVERHANDLER_H
#define SPIN_SERVERHANDLER_H

#include "Models/SensorData.h"
#include "AppServer.h"
#include "Models/ControlData.h"
#include <thread>

class ServerHandler {
private:
public:
    ServerHandler(SensorData &sensorData, ControlData &controlData, std::vector<int>  *servoData) {
        serverThread = std::thread(&ServerHandler::start,this);
        dataToJSON(sensorData, controlData, servoData);
    }
    std::thread serverThread;
    AppServer server;
    virtual ~ServerHandler() { serverThread.join(); }

    void start();

    void dataToJSON(SensorData &sensorData, ControlData &controlData, std::vector<int>  *servoData);
};


#endif //SPIN_SERVERHANDLER_H
