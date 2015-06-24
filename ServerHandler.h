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
    SensorData *sensorData;
    ControlData *controlData;
    std::vector<int> *servoData;
    ServerHandler(SensorData *sensorData, ControlData *controlData, std::vector<int>  *servoData):sensorData(sensorData),controlData(controlData),servoData(servoData) {
        serverThread = std::thread(&ServerHandler::start,this);
    }
    std::thread serverThread;
    std::thread updateThread;
    AppServer server;
    virtual ~ServerHandler() { serverThread.join();  updateThread.join(); }

    void sendValues(AppServer &server);
    void start();
    void createLeg(std::string &result, float temp, float r1, float t1, float r2, float t2, float r3, float t3, bool last);

    std::string dataToJSON(SensorData &sensorData, ControlData &controlData, std::vector<int> &servoData);
};


#endif //SPIN_SERVERHANDLER_H
