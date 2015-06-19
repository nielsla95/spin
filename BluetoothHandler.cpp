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
    char buf[1024];
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
        usleep(2000000);
        return listen(controlData);
    }else{
        do{
            // KIJK WANNEER IK KAN VERBINDEN
            if( status < 0 ){
                perror("uh oh");
                usleep(2000000);
                // ZO NIET DAN VERBINDING IK OPNIEUW
                return listen(controlData);
            }
            // len = lengte van s en schrijft naar buf
            len = read(s, buf, 200);
            if( len>0 ) {
                buf[len]=0;
                output += buf;

                int startIndex = -1;
                int endIndex = -1;

                for(int i = 0; i < output.length(); i++)
                {
                    if(startIndex == -1 && output[i] == '<') startIndex = i;
                    if(endIndex == -1 && startIndex <  i && output[i] == '>') endIndex = i;
                }

                if(startIndex != -1 && endIndex != -1){
                    std::string fixedOutput = output.substr(startIndex, endIndex);
                    controlData.set(output);
                    std::cout << "OUTPUT BLUETOOTH: " << output << std::endl;
                    output = "";
                }
            }
        }while(len>0);

        close(s);
    }
}