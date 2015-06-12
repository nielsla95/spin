//
// Created by niels on 10-6-15.
//

#include <iostream>
#include <string.h>
#include "BluetoothHandler.h"

void BluetoothHandler::start()
{
    std::cout << "Looking for bluetooth controller! O.o" << std::endl;

    std::string name = "groep1";

    bool connected = false;
    bdaddr_t controllerDevice;
    while(!connected){
        controllerDevice = findDevicesByName(name, connected);
        if(!connected)
            std::cout << "Bluetooth controller wasn't found, retry..." << std::endl;
    }

    while(true) {
        crap();
        sleep(1);
        std::cout << ".";
    }
}

bdaddr_t BluetoothHandler::findDevicesByName(const std::string &deviceName, bool &success)
{
    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i;
    char addr[19] = { 0 };
    char name[248] = { 0 };

    dev_id = hci_get_route(NULL);
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        exit(1);
    }

    len  = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));

    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if( num_rsp < 0 ) perror("hci_inquiry");

    bdaddr_t returnAddress = {{0, 0, 0, 0, 0, 0}};

    for (i = 0; i < num_rsp; i++) {
        returnAddress = (ii+i)->bdaddr;
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name),
                                 name, 0) < 0)
            strcpy(name, "[unknown]");
        printf("%s  %s\n", addr, name);
        if(name == deviceName) {
            returnAddress = (ii + i)->bdaddr;
            success = true;
            std::cout << "We found the controller :D" << std::endl;
        }
    }

    free( ii );
    close( sock );

    return returnAddress;
}


void BluetoothHandler::crap()
{
    bdaddr_t anydbaddr = {{0, 0, 0, 0, 0, 0}};
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = anydbaddr;
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // read data from the client
    bytes_read = read(client, buf, sizeof(buf));
    if( bytes_read > 0 ) {
        printf("received [%s]\n", buf);
    }

    // close connection
    close(client);
    close(s);
}

BluetoothData BluetoothHandler::get() { // todo: fill in bluetoothdata class
    return BluetoothData();
}
