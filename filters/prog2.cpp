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

int main()
{
	string file_name;
	cout<<"Which image? (Choose from img_in folder. Must have .jpg extension)"<<endl;
	cin>>file_name;
	//Mat img = imread("../img_in/imagen2.jpg",CV_LOAD_IMAGE_COLOR);
    //Mat img_gray = imread("../img_in/imagen1.jpg",IMREAD_GRAYSCALE);
    Mat img = imread("./img_in/"+file_name+".jpg",CV_LOAD_IMAGE_COLOR);
    Mat img_gray;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    cout<<"Channels in img:\t"<<img.channels()<<endl;
	cout<<"Channels in img_gray:\t"<<img_gray.channels()<<endl;
    imshow("Img original", img);
    imshow("Gray scale",img_gray);
    Mat img_color;
    applyColorMap(img_gray, img_color, COLORMAP_HSV);
    cout<<"Channels in img_color:\t"<<img_color.channels()<<endl;
    imshow("Color map",img_color);

	// Channels
  	// channels is a vector of 3 matrix
    vector<Mat> chan(3);
    Mat ch1, ch2, ch3;
    split(img, chan);
	// Get the channels
	ch1 = chan[0]; // B
	ch2 = chan[1]; // G
	ch3 = chan[2]; // R
	imshow("Blue Channel", ch1);
	imshow("Green Channel", ch2);
	imshow("Red Channel", ch3);
	

	// Different color models
	Mat img_hsv,img_hls,img_lab,img_luv, img_crcb;
	cvtColor(img, img_hsv, CV_BGR2HSV); // use CV_BGR... because it's the default channels order in opencv
	cvtColor(img, img_hls, CV_BGR2HLS);
	cvtColor(img, img_lab, CV_BGR2Lab);
	cvtColor(img, img_luv, CV_BGR2Luv);
	cvtColor(img, img_crcb,CV_BGR2YCrCb);

	imshow("HSV", img_hsv);
	imshow("HSL", img_hls);
	imshow("Lab", img_lab);
	imshow("Luv", img_luv);
	imshow("CrCb", img_crcb);

    waitKey(0);
    cout<<"Goodbye!"<<endl;

    return 0;
}