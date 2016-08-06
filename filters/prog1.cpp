/*
From this tutorial
http://www.learnopencv.com/applycolormap-for-pseudocoloring-in-opencv-c-python/

*/
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std; // for the cout...

//VideoCapture cap(0); // Web cam
VideoCapture capWeb(0); // web cam

int main()
{
	capWeb.set(CV_CAP_PROP_FRAME_WIDTH, 352); // columns |
	capWeb.set(CV_CAP_PROP_FRAME_HEIGHT, 288); // rows ---
	bool stop = false;
	Mat currentImage = Mat(352, 288, CV_8UC3);
	//Mat currentImage = Mat(240, 320, CV_8UC3);
	Mat dst, my_kernel;
	int kernel_size;

	while(stop==false) {
		char key = waitKey(5);
		switch (key) {
            case 27: stop = true; break;
		}
		//cap >> img;
		capWeb >> currentImage;

		//imshow("computer", imgC);
		imshow("webcam", currentImage);
		// Mean Filter 5x5
    	kernel_size=5;
    	my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04
	    ); // it's 1/25
    	filter2D(currentImage, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
	    imshow("5x5 Mean filter", dst);
		
	}

    cout<<"Goodbye!"<<endl;

    return 0;
}