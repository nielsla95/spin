//
// Created by Tjipkevdh on 15-6-2015.
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <unistd.h>
#include "Commands/ICommand.h"

#ifndef IDP2015_VISION_H
#define IDP2015_VISION_H

using namespace std;
using namespace std::chrono;
using namespace cv;
class Vision {

public:
    Mat image;
    Mat image2;
    milliseconds ms;
    int streamcount = 1;
    int erosion_type;
    int erosion_elem = 0;
    int erosion_size = 3;
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    int *x;
    int *y;
    int *balloon;
    std::thread visionThread;

    Vision(int *x, int *y, int *balloon) :x(x), y(y), balloon(balloon) {
        visionThread = std::thread(&Vision::startVision,this);
    }

    virtual ~Vision() { visionThread.join(); }

    void recognizeBlueBalloon();
    void recognizeRedBalloon();
    void fillEdgeImage(Mat edgeIn, Mat& filledEdgesOut);
    void findBiggestContour();
    void liveStream();
    void startVision();


private:

};

#endif