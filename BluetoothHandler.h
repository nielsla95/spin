//
// Created by niels on 10-6-15.
//

#ifndef SPIN_BLUETOOTHHANDLER_H
#define SPIN_BLUETOOTHHANDLER_H


#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <rfcomm.h>
#include <thread>
#include "BluetoothHandler.h"
#include "Models/BluetoothData.h"

class BluetoothHandler {

public:
    std::thread bluetoothHandlerThread;

    BluetoothHandler() { bluetoothHandlerThread = std::thread(&BluetoothHandler::start,this); }
    virtual ~BluetoothHandler() { bluetoothHandlerThread.join(); }

    void start();
    bdaddr_t findDevicesByName(const std::string &deviceName, bool &success);
    void crap();

    BluetoothData get();
};


#endif //SPIN_BLUETOOTHHANDLER_H
