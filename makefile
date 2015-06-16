all:
	g++ -o build/spin -pthread dynamixel.h dynamixel.c dxl_hal.c dxl_hal.h *.cpp Commands/*.cpp  -lbluetooth  -lboost_system -std=c++11
