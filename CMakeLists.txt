cmake_minimum_required(VERSION 3.2)
project(Spin)

#debug with warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -O2 -pthread -std=c++11 -lbluetooth -lboost_system")
#without warnings hurhyes seflsaejfajsehfas
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -lbluetooth -lboost_system")

INCLUDE_DIRECTORIES(/usr/include/boost)
LINK_DIRECTORIES(/usr/include/boost)

INCLUDE_DIRECTORIES(/usr/include/websocketpp)
LINK_DIRECTORIES(/usr/include/websocketpp)

INCLUDE_DIRECTORIES(/usr/include/bluetooth)
LINK_DIRECTORIES(/usr/include/bluetooth)

set(SOURCE_FILES main.cpp)
set(dynamixel.h)

add_executable(Spin ${SOURCE_FILES} dxl_hal.c dxl_hal.h dynamixel.c dynamixel.h Models/Servo.h Models/Leg.h Controller.cpp Controller.h ServoDriver.cpp ServoDriver.h Monitor.cpp Monitor.h ServerHandler.cpp ServerHandler.h Models/SensorData.h Commands/ICommand.h Commands/WalkCommand.cpp Commands/WalkCommand.h BluetoothHandler.cpp BluetoothHandler.h Models/ControlData.h AppServer.h)
TARGET_LINK_LIBRARIES(Spin bluetooth boost_system)