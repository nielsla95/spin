//
// Created by eele on 9-6-2015.
//

#include "ServerHandler.h"

void ServerHandler::start() {

    retry:
    std::cout << "Web Socket trying to connect..." << std::endl;
    try{
        updateThread = std::thread(&ServerHandler::sendValues, this, std::ref(server));
        server.run(9005);
    } catch(const std::exception &e) {
        std::cout << "Web Socket server couldn't be started! let's restart" << std::endl;
        updateThread.join();
        sleep(5);
        goto retry;
    }

}

void ServerHandler::sendValues(AppServer &server)
{
    //std::cout << "SEND CRAP LOOP INITZ" << std::endl;
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

    std::cout << "servo data length: " << servoData.size() << std::endl;
    std::cout << "servo data pointer: " << &servoData << std::endl;
    //std::cout << "JA IK BEREIK LEUKE CODE "<<std::endl;
    std::vector<int> testServoData = servoData;
    for (int i = 0; i < testServoData.size(); ++i) {
        std::cout << "JA JOEPIE: " << testServoData.at(i) << std::endl;
    }
    //std::cout << "size = 0 ;( "<<std::endl;
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
    result += "\"Leg\":[";


    /*try
    {
        std::vector<int> servoPos;
        std::vector<int> servoTemp;
        std::vector<int> servoRot;

        for(int i = 0; i < servoData.size(); i++)
        {
            if(i <= 18)
            {
                servoPos.push_back(servoData[i]);
            }
            else if(i <= 36)
            {
                servoPos.push_back(servoTemp[i]);
            }
            else
            {
                servoPos.push_back(servoRot[i]);
            }
        }
        //std::string &result, float temp, float r1, float t1, float r2, float t2, float r3, float t3, bool last)
        for(int i = 0; i < 6; i++)
        {
            float temp = servoTemp[i] + servoTemp[i+1] + servoTemp[i+2];
            bool isLast = i == 6;

            createLeg(result, temp, servoRot[i], servoPos[i], servoRot[i+1], servoPos[i+1], servoRot[i+2], servoPos[i+2], isLast);
        }
    }
    catch(std::exception e)
    {
        createLeg(result, 0, 0, 0, 0, 0, 0, 0, false);
        createLeg(result, 0, 0, 0, 0, 0, 0, 0, false);
        createLeg(result, 0, 0, 0, 0, 0, 0, 0, false);
        createLeg(result, 0, 0, 0, 0, 0, 0, 0, false);
        createLeg(result, 0, 0, 0, 0, 0, 0, 0, false);
        createLeg(result, 0, 0, 0, 0, 0, 0, 0, true);
    }*/

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