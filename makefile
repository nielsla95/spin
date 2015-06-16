all:
	g++ -o build/spin -pthread dynamixel.h dynamixel.c dxl_hal.c dxl_hal.h *.cpp Commands/*.cpp  -lbluetooth  -lboost_system -L/usr/include/websocketpp -std=c++11
