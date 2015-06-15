cmake_minimum_required(VERSION 3.2)
project(Spin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -O2 -pthread -std=c++11 -lbluetooth")

INCLUDE_DIRECTORIES(/usr/include/bluetooth)
LINK_DIRECTORIES(/usr/include/bluetooth)

set(SOURCE_FILES main.cpp)
set(dynamixel.h)

add_executable(Spin ${SOURCE_FILES} dxl_hal.c dxl_hal.h dynamixel.c dynamixel.h Models/Servo.h Models/Leg.h Controller.cpp Controller.h ServoDriver.cpp ServoDriver.h Monitor.cpp Monitor.h ServerHandler.cpp ServerHandler.h Models/SensorData.h Commands/ICommand.h Commands/WalkCommand.cpp Commands/WalkCommand.h BluetoothHandler.cpp BluetoothHandler.h Models/ControlData.h Commands/PoleCommand.h Commands/PoleCommand.cpp Commands/DanceCommand.h Commands/DanceCommand.cpp Commands/GapCommand.h Commands/GapCommand.cpp Commands/BalloonCommand.h Commands/BalloonCommand.cpp Commands/GateCommand.h Commands/GateCommand.cpp)
TARGET_LINK_LIBRARIES(Spin bluetooth)