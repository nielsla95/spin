cmake_minimum_required(VERSION 3.2)
project(Spin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Spin ${SOURCE_FILES} Servo.cpp Servo.h Leg.cpp Leg.h Controller.cpp Controller.h ServoDriver.cpp ServoDriver.h Monitor.cpp Monitor.h ServerHandler.cpp ServerHandler.h sensorData.cpp sensorData.h ICommand.cpp ICommand.h IMovement.cpp IMovement.h DefaultMovement.cpp DefaultMovement.h WalkCommand.cpp WalkCommand.h)