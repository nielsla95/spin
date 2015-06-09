cmake_minimum_required(VERSION 3.2)
project(Spin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Spin ${SOURCE_FILES} Servo.cpp Servo.h Leg.cpp Leg.h Controller.cpp Controller.h ServoDriver.cpp ServoDriver.h)