//
// Created by Tjipkevdh on 15-6-2015.
//

#include "Vision.h"

void Vision::recognizeBlueBalloon()
{
    //threshold...
    // Dont change this values pl0x :3
    //inRange(image, Scalar(0,90,90),  Scalar(30,260,260), image);
    inRange(image, Scalar(90, 150,90), Scalar(130,260,260),image);
}
void Vision::recognizeRedBalloon() {

    //image 1
    //inRange(image, Scalar(120,100,100),  Scalar(140,260,260), image);
    inRange(image, Scalar(140,0,0), Scalar(160,260,260),image2);
    inRange(image,Scalar(160,50,100),Scalar(180,260,260), image);
}


void Vision::fillEdgeImage(Mat edgeIn, cv::Mat &filledEdgesOut)
{
    Mat edgesNeg = edgeIn.clone();

    floodFill(edgesNeg, Point(0,0), CV_RGB(255,255,255));
    bitwise_not(edgesNeg, edgesNeg);
    filledEdgesOut = (edgesNeg | edgeIn);

    return;
}
void Vision::findBiggestContour()
{
    int largest_area=0;
    int largest_contour_index=0;
    Rect bounding_rect;

    for( int i = 0; i < contours.size(); i++ ) // iterate through each contour.
    {
        double a = contourArea( contours[i],false);  //  Find the area of contour
        if(a>largest_area){
            largest_area=a;
            largest_contour_index=i;                //Store the index of largest contour
            bounding_rect=boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
        }

    }
    Scalar color(255,255,255);
    drawContours( image, contours,largest_contour_index, color, CV_FILLED, 8, hierarchy );// Draw the largest contour using previously stored index.
    Point center(bounding_rect.x + bounding_rect.size().width/2, bounding_rect.y + bounding_rect.size().height/2);
    rectangle(image, bounding_rect, Scalar(0,255,0),1, 8,0);
    *x = center.x;
    *y = center.y;

    //std::cout << "center of countour is " << center.x << "+ " << center.y << std::endl;
}



void Vision::liveStream()
{
    long duration = 100;
    if(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - ms.count() >= duration)
    {
        ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

        imwrite("stream" + std::to_string(streamcount) + ".jpg", image);
        std::cout << "streamcount: " << streamcount<< std::endl;
        streamcount++;
    }
}

void Vision::startVision()// todo: WaitKey(0); achter imshow maakt het werkend :p
{

    cout << "vision gestart" << endl;

    if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
    else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
    else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

    Mat element = getStructuringElement( erosion_type,
                                         Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                         Point( erosion_size, erosion_size ) );
    //VideoCapture cap(0);
    VideoCapture videocapture(0);
    //videocapture.open(0);
    if(!videocapture.isOpened()) // check if we succeeded
    {
        std::cout << "camera not opened :(" << std::endl;
        return;
    }
    else
        std::cout << "cam opened: " << std::endl;

    while(1)
    {// todo: cout uitgecomment hier
        // cout << "zit nu in while loopyswoopy" << std::endl;
        // Getting the image from the camm..
        videocapture >> image;
        //waitKey(0);
        //cout << "hier zou een image geshowed moeten worden" << endl;
        //imshow("testbestand", image);
//getchar();

        /*liveStream();
        if(streamcount == 10)
        {
            streamcount = 1;
        }*/



        Size size(image.cols/2,image.rows/2);
        //std::cout << size << endl;


        resize(image,image,size);

        cvtColor(image,image,CV_BGR2HSV);

        if(*balloon==1)
        {
            recognizeBlueBalloon();
        }
        else
        {
            recognizeRedBalloon();
        }


        fillEdgeImage(image,image);






        /// Apply the erosion operation
        erode( image, image, element);
        dilate(image,image,element);



        //namedWindow("Display Image2", WINDOW_AUTOSIZE );
        //imshow("Display Image2", image2);

        Canny(image,image,100,200,3);
        findContours(image, contours,hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
        findBiggestContour();
        //cout << "x: " << x << ", y: " << y << "." << endl;

//        if(*x > 0)	{
//            std::cout << "ziet ballon :D, x: " << *x << ", y: " << *y << std::endl;
//        }
//        else if(*y > 0)
//        {
//            std::cout << "ziet ballon :D, x: " << *x << ", y: " << *y << std::endl;;
//        }
//        else
//        {
//            std::cout << "kijkt rond" << std::endl;
//        }
        //namedWindow("Display Image", WINDOW_AUTOSIZE );
        //imshow("Display Image", image);
    }
    //waitKey(0);

    return;
}