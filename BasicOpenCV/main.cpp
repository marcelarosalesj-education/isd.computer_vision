#include <stdio.h>
#include <iostream>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <string>

using namespace cv;
using namespace std;

int main(void)
{
    printf("%s\r\n", CV_VERSION);
    printf("%u.%u.%u\r\n", CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION);

    string file_name;
    file_name = "imagen1.jpg";
    Mat img;
    img = imread("./img_in/"+file_name+".jpg");
    namedWindow( "Image", CV_WINDOW_AUTOSIZE );
	imshow("Image", img);

	waitKey(0);
    cout<<"Goodbye!"<<endl;

    return 0;
}