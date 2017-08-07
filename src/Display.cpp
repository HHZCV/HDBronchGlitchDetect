#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2/video/tracking.hpp"
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame,diff,testPattern;
    namedWindow("video",1);

    for(;;)
    {
    	double t=(double)cv::getTickCount();
        cap >> frame; // get a new frame from camera
        compare(frame,testPattern,diff,CMP_NE);
        imshow("video", frame);
        if(waitKey(30) >= 0) break;
        t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();// elapsed time in sec
        std::cout << "I am working at " << 1.0/t << " FPS" << std::endl;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
