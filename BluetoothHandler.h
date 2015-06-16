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
#include <bluetooth/rfcomm.h>
#include <thread>
#include "BluetoothHandler.h"
#include "Models/ControlData.h"

class BluetoothHandler {

public:
    std::thread bluetoothHandlerThread;

    BluetoothHandler(ControlData &controlData)
    {
        bluetoothHandlerThread = std::thread(&BluetoothHandler::listen,this,std::ref(controlData));
    }

    virtual ~BluetoothHandler() { bluetoothHandlerThread.join(); }

    void listen(ControlData &controlData);
};


#endif //SPIN_BLUETOOTHHANDLER_H
