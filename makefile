all:
	g++ -pthread *.cpp Commands/*.cpp Models/*.cpp Movements/*.cpp -std=c++11 -lbluetooth
