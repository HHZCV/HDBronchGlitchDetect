#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2/video/tracking.hpp"
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>

using namespace cv;
using namespace std;

int main(int, char**)
{
	Mat img1,img2,img1_img2;
	img1=imread("C:\\Users\\huzhu\\workspace\\HDBronchGlitchDetect\\HDBronchGlitchDetect\\src\\a.tiff");
	img2=imread("C:\\Users\\huzhu\\workspace\\HDBronchGlitchDetect\\HDBronchGlitchDetect\\src\\b.tiff");
    absdiff(img1,img2,img1_img2);
    Mat bgr[3];   //destination array
    split(img1_img2,bgr);//split source
    bool eq=(((cv::countNonZero(bgr[0])==0) && (cv::countNonZero(bgr[1])==0))&&(cv::countNonZero(bgr[2])==0));
    cout<<"eq="<<eq<<endl;
    multiply(img1_img2,100,img1_img2);
    namedWindow("img1_img2",1);
    imshow("img1_img2",img1_img2);

   /*
   // VideoCapture cap(0); // open the default camera
    VideoCapture cap("C:\\Users\\huzhu\\workspace\\HDBronchGlitchDetect\\HDBronchGlitchDetect\\src\\testPatternVideo.mp4");
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat diff,testPattern;

    namedWindow("video",1);
    namedWindow("testPattern",1);
    namedWindow("diff",1);

    time_t currentTime;
    struct tm *timeinfo;
    int i=0;

    for(;;)
    {
    	Mat frame;
    	double t=(double)cv::getTickCount();
        if (i<3)
        {
        	cap>>testPattern;
        	imshow("testPattern",testPattern);
        }else{
        	cap >> frame; // get a new frame from camera

        	absdiff(frame,testPattern,diff);//diff should be all zero if two images are identical
        	imshow("diff",diff);

        	bool eq=(cv::countNonZero(bgr[1])==0);
        	 if (~eq)
        	        {
        		        cout<<"glitch detected"<<endl;
        	        	time(&currentTime);
        	        	timeinfo=localtime(&currentTime);
        	        	String imageName=asctime(timeinfo);
        	        	cout<<imageName<<endl;
        	        	//imwrite(imageName,frame);
        	        }else{
        	        	cout<<"good"<<endl;
        	        }

        if(frame.empty())
        {
        	cout<<"fail to open video"<<endl;
        }else
        {
        	 imshow("video", frame);
        }
        if(waitKey(30) >= 0) break;
        }
        t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();// elapsed time in sec
        //std::cout << "I am working at " << 1.0/t << " FPS" << std::endl;
        i++;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    */
    waitKey();
    return 0;
}
