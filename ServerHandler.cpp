//
// Created by eele on 9-6-2015.
//

#include "ServerHandler.h"

void ServerHandler::start() {

    updateThread = std::thread(&ServerHandler::sendValues, this, std::ref(server));

    try{
        server.run(9005);
    } catch(const std::exception &e) {
        std::cout << "Web Socket server couldn't be started!" << std::endl;
    }

}

void ServerHandler::sendValues(AppServer &server)
{
    std::cout << "SEND CRAP LOOP INITZ" << std::endl;
    while(true) {
        if (server.hdlReady) {

            std::string Json = dataToJSON(*sensorData, *controlData, *servoData);
            server.sendLoop(Json);
            std::cout << "Sending crap websuckets" << std::endl;
        }
        usleep(1000000);
    }
}

void ServerHandler::createLeg(std::string &result, float temp, float r1, float t1, float r2, float t2, float r3, float t3, bool last)
{
    result += "{";
    result += "\"Temperature\":" + std::to_string(temp) + ",";
    result += "\"Servo\":[";
    result += "{";
    result += "\"rotation\":"+ std::to_string(r1) + ",";
    result += "\"temperature\":" + std::to_string(t1);
    result += "},";
    result += "{";
    result += "\"rotation\":" + std::to_string(r2) + ",";
    result += "\"temperature\":" + std::to_string(t2);
    result += "},";
    result += "{";
    result += "\"rotation\":" + std::to_string(r3) + ",";
    result += "\"temperature\":" + std::to_string(t3);
    result += "}";
    result += "]";
    result += "}";

    if(!last)
        result += ",";
}

std::string ServerHandler::dataToJSON(SensorData &sensorData, ControlData &controlData, std::vector<int> &servoData){

//    SensorData sensorData = *sensorDataz;
//    ControlData controlData = *controlDataz;
//    std::vector<int> servoData = *servoDataz;

    std::cout << "JA IK BEREIK LEUKE CODE "<<std::endl;
    std::vector<int> testServoData = servoData;
    for (int i = 0; i < testServoData.size(); ++i) {
        std::cout << "JA JOEPIE: " << testServoData.at(i) << std::endl;
    }
    std::cout << "size = 0 ;( "<<std::endl;
    std::string result;
    // convert to json string

    result += "{";
    //Add the results from the sensor
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

    //Add the results from the control
    result += "\"Control\":{";
    result += "\"balloon\":\"";
    result += std::to_string(controlData.balloon) + "\",";
    result += "\"killswitch\":\"";
    result += std::to_string(controlData.killSwitch) + "\",";
    result += "\"mode\":\"";
    result += std::to_string(controlData.mode) + "\",";
    result += "\"speed\":\"";
    result += std::to_string(controlData.speed) + "\",";
    result += "\"x\":\"";
    result += std::to_string(controlData.x) + "\",";
    result += "\"y\":\"";
    result += std::to_string(controlData.y) + "\",";
    result += "\"z\":\"";
    result += std::to_string(controlData.z) + "\"";
    result += "},";

    //Add the results from the legs
    //result += "\"Leg\"":[ { "Temperature":183, "Servo": [ {"id":1, "rotation":199, "temperature":116}, {"id":2, "rotation":80, "temperature":307}, {"id":3, "rotation":216, "temperature":97} ] }, { "Temperature":14, "Servo": [ {"id":1, "rotation":198, "temperature":274}, {"id":2, "rotation":312, "temperature":203}, {"id":3, "rotation":114, "temperature":285} ] }, { "Temperature":179, "Servo": [ {"id":1, "rotation":292, "temperature":284}, {"id":2, "rotation":299, "temperature":47}, {"id":3, "rotation":5, "temperature":31} ] }, { "Temperature":98, "Servo": [ {"id":1, "rotation":292, "temperature":258}, {"id":2, "rotation":182, "temperature":305}, {"id":3, "rotation":339, "temperature":310} ] }, { "Temperature":162, "Servo": [ {"id":1, "rotation":166, "temperature":244}, {"id":2, "rotation":327, "temperature":344}, {"id":3, "rotation":171, "temperature":53} ] }, { "Temperature":223, "Servo": [ {"id":1, "rotation":67, "temperature":232}, {"id":2, "rotation":23, "temperature":54}, {"id":3, "rotation":26, "temperature":201} ] } ]};
    result += "\"Leg\":[";

    createLeg(result, 0, 0, 0, 0, 0, 0, 0, false);
    createLeg(result, 0, 0, 0, 0, 0, 0, 0, false);
    createLeg(result, 0, 0, 0, 0, 0, 0, 0, false);
    createLeg(result, 0, 0, 0, 0, 0, 0, 0, false);
    createLeg(result, 0, 0, 0, 0, 0, 0, 0, false);
    createLeg(result, 0, 0, 0, 0, 0, 0, 0, true);

    result += "]";
    result += "}";

    return result;
    // send to server
    //server.setJsonData(result);
}