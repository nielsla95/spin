//
// Created by eele on 9-6-2015.
//

#include "ServerHandler.h"

void ServerHandler::start() {
    server.run(9002);
}

void ServerHandler::dataToJSON(SensorData &sensorData, ControlData &controlData){
    std::string result;
    // convert to json string

    result += "{";
        result += "\"Sensor\":{";
            result += "\"Voltage\":\"";
            result += std::to_string(sensorData.voltage) + "\",";
            result += "\"Ampere\":\"";
            result += std::to_string(sensorData.ampere) + "\",";
            result += "\"Temp\":\"";
            result += std::to_string(sensorData.temp) + "\",";
            result += "\"gyx\":\"";
            result += std::to_string(sensorData.gyX) + "\",";
            result += "\"gyy\":\"";
            result += std::to_string(sensorData.gyY) + "\",";
            result += "\"gyz\":\"";
            result += std::to_string(sensorData.gyZ) + "\"";
        result += "},";

    result += "};";

    // send to server
    server.setJsonData(result);
}