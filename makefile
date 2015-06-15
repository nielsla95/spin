all:
	g++-4.7 -o build/spin -pthread dynamixel.h dynamixel.c dxl_hal.c dxl_hal.h *.cpp Commands/*.cpp  -lbluetooth -std=c++11
