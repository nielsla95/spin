//
// Created by root on 16-6-15.
//

#ifndef SPIN_APPSERVER_H
#define SPIN_APPSERVER_H

#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <thread>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

class AppServer {


public:
    //std::string jsonObject;
    connection_hdl newestHDL;
    bool hdlReady = false;
    void sendLoop(std::string &jsonObject)
    {
        std::cout << "Sending from websocket loop" << std::endl;
        this->m_server.send(this->newestHDL, jsonObject, websocketpp::frame::opcode::TEXT);
        sleep(2);
    }

    //std::thread serverT;
    AppServer(){
        m_server.init_asio();

        m_server.set_open_handler(bind(&AppServer::on_open,this,::_1));
        m_server.set_close_handler(bind(&AppServer::on_close,this,::_1));
        m_server.set_message_handler(bind(&AppServer::on_message,this,::_1,::_2));


        //serverT = std::thread(&sendLoop, this);
    }

    void on_open(connection_hdl hdl) {
        //this->m_server.send(hdl, jsonObject, websocketpp::frame::opcode::TEXT);
        this->newestHDL = hdl;
        this->hdlReady = true;
    }

    void on_close(connection_hdl hdl) {
        m_connections.erase(hdl);
    }

    void on_message(connection_hdl hdl, server::message_ptr msg) {
        for (auto it : m_connections) {
            m_server.send(it,msg);
        }
    }

    void run(uint16_t port) {
        m_server.listen(port);
        m_server.start_accept();
        m_server.run();
    }

//    void setJsonData(std::string input) {
//        this->jsonObject = input;
//        std::cout << "jsonObject: " << jsonObject << std::endl;
//    }

    ~AppServer() {
        //serverT.join();
        m_server.stop_listening();
        m_server.stop();
    }
private:
    typedef std::set<connection_hdl,std::owner_less<connection_hdl>> con_list;

    server m_server;
    con_list m_connections;
};

#endif //SPIN_APPSERVER_H