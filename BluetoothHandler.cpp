//
// Created by niels on 10-6-15.
//

#include <iostream>

#include "BluetoothHandler.h"

// MacAddress: 00:0B:53:13:15:3C

void BluetoothHandler::listen(ControlData &controlData)
{
    std::cout << "Looking for bluetooth controller! O.o" << std::endl;
    struct sockaddr_rc addr = { 0 };
    int s, status, len;
    char dest[18] = "00:0B:53:13:15:3C";
    char buf[2048];
    std::string output;

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    if( status == 0 ) {
        //status = write(s, "hello!", 6);
    }

    if( status < 0 ){
        perror("uh oh");
        return listen(controlData);
    }else{
        do{
            if( status < 0 ){
                perror("uh oh");
                return listen(controlData);
            }
            len = read(s, buf, sizeof buf);
            if( len>0 ) {
                buf[len]=0;
                output += buf;
                std::cout << output << std::endl;
                controlData.set(output);
            }
        }while(len>0);

        close(s);
    }
}