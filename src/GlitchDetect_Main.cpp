#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2/video/tracking.hpp"
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int, char**)

{
	cout<<"enter camera ID"<<endl;
	int cameraID;
	cin>>cameraID;

    VideoCapture cap(cameraID); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    namedWindow("preview",1);
    cout<<"press any key when ready to capture test pattern"<<endl;
    for(;;)
    {
    	Mat preview;
    	cap>>preview;
    	imshow("preview",preview);
    	if(waitKey(15) >= 0) break;
    }

    Mat diff,testPattern;

   // namedWindow("video",1);
    //namedWindow("testPattern",1);
   // namedWindow("diff",1);

    int i=0;
    for(;;)
    {
    	Mat frame;
        if (i==0)
        {
        	cap>>testPattern;
        	//imshow("testPattern",testPattern);

        }else{
        	double t=(double)cv::getTickCount();
        	cap >> frame; // get a new frame from camera

        	absdiff(frame,testPattern,diff);//diff should be all zero if two images are identical

        	//imshow("diff",diff);
        	Mat bgr[3];   //destination array
        	split(diff,bgr);//split source
        	bool eq=(((cv::countNonZero(bgr[0])==0) && (cv::countNonZero(bgr[1])==0))&&(cv::countNonZero(bgr[2])==0));

        	 if (eq==0)
        	        {
        		        cout<<"eq="<<eq<<" glitch detected"<<endl;
                        std::string imageName;
                        ostringstream convert;
                        convert<<i;
						imageName=convert.str()+ ".bmp";
        	        	cout<<imageName<<endl;
        	        	imwrite(imageName,frame);
        	        }else{
        	        	cout<<"eq="<<eq<<" good"<<endl;
        	        }

        	        	 imshow("preview", frame);
        	        	 if(waitKey(15) >= 0) break;

        	 t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();// elapsed time in sec
        	 std::cout << "FPS= " << 1.0/t << " FPS" << std::endl;

        }
        i++;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor

    waitKey(0);
    return 0;
}
