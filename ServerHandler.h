////
//// Created by eele on 9-6-2015.
////
//
//#ifndef SPIN_SERVERHANDLER_H
//#define SPIN_SERVERHANDLER_H
//
//#include <websocketpp/config/asio_no_tls.hpp>
//
//#include <websocketpp/server.hpp>
//#include "Models/SensorData.h"
//#include <thread>
//
//class ServerHandler {
//private:
//
//public:
//    std::thread serverThread;
//
//    ServerHandler(SensorData &sensorData) { serverThread = std::thread(&ServerHandler::start,this,std::ref(sensorData)); }
//    virtual ~ServerHandler() { serverThread.join(); }
//
//    void start(SensorData &sensorData);
//};
//
//
//#endif //SPIN_SERVERHANDLER_H
