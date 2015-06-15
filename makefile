all:
	g++ -o build/spin -pthread dynamixel.h dynamixel.c dxl_hal.c dxl_hal.h *.cpp Commands/*.cpp  libluetooth  liboost_system -std=c++11
