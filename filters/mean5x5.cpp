/*
 * Mean filter 5x5
 * */

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

VideoCapture cap(0);

Mat generate_kernel_0p4() {
    int kernel_size = 5;
    Mat kernel= (Mat_<double>(kernel_size,kernel_size) <<
            0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04
    );
    return kernel;
}


int main() {
	// Variable declaration
    bool stop = false;
	Mat original_image = Mat(352, 288, CV_8UC3);
	Mat filtered_image;

    // Capture image
    if(!cap.isOpened())
        return -1;
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 352);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

	while(stop==false) {
		char key = waitKey(5);
		switch (key) {
            case 27: stop = true; break;
		}
		cap >> original_image;

		imshow("webcam", original_image);
		
        // Mean Filter 5x5
        Mat my_kernel = generate_kernel_0p4();

    	filter2D(original_image, filtered_image, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT);
	    imshow("5x5 Mean filter", filtered_image);
	}

    return 0;
}
