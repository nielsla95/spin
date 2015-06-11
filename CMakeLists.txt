cmake_minimum_required(VERSION 3.2)
project(Spin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -O2 -pthread -std=c++11 -lbluetooth")

INCLUDE_DIRECTORIES(/usr/include/bluetooth)
LINK_DIRECTORIES(/usr/include/bluetooth)

set(SOURCE_FILES main.cpp)
set(dynamixel.h)

add_executable(Spin ${SOURCE_FILES} dxl_hal.c dxl_hal.h dynamixel.c dynamixel.h Models/Servo.cpp Models/Servo.h Models/Leg.cpp Models/Leg.h Controller.cpp Controller.h ServoDriver.cpp ServoDriver.h Monitor.cpp Monitor.h ServerHandler.cpp ServerHandler.h Models/SensorData.cpp Models/SensorData.h Commands/ICommand.h Movements/IMovement.cpp Movements/IMovement.h Movements/DefaultMovement.cpp Movements/DefaultMovement.h Commands/WalkCommand.cpp Commands/WalkCommand.h BluetoothHandler.cpp BluetoothHandler.h)
TARGET_LINK_LIBRARIES(Spin bluetooth)