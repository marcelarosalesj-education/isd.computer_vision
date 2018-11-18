/*
From this tutorial
http://www.learnopencv.com/applycolormap-for-pseudocoloring-in-opencv-c-python/

*/
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <experimental/filesystem>

using namespace cv;
using namespace std;
namespace fs = std::experimental::filesystem;

std::vector<fs::directory_entry> get_images() {
    std::vector<fs::directory_entry> ret;
    string path  = "../images";
    for (auto & p : fs::directory_iterator(path)) {
        ret.push_back(p);
    }
    return ret;
}

void show_options(vector<fs::directory_entry> options) {
    int counter = 1;
    for(auto i = options.begin(); i != options.end(); ++i) {
        cout << counter <<") ";
        cout << *i << endl;
        counter++;
    }
    cout << "0) Quit program" << endl;
}

int main()
{
    // Variables
    int opt;
    bool selection = false;
    Mat img;
    Mat img_gray;

    // Selection 
    std::vector<fs::directory_entry> options = get_images();
    cout << "Select an image:" << endl;
    show_options(options);
    while(!selection) {
        cin >> opt;
        if(opt == 0){
            cout << "Exiting program..." << endl;
            return 0;
        } else if(opt < 0 || opt > options.size() ){
            cout << "Selection out of range. Try again."<<endl;
        } else {
            selection = true;
        }
    }

    cout << "It was selected: " << endl;
    cout << options[opt-1] << endl;
    
    // Basic program
    string file_name = options[opt-1].path();
    img = imread(file_name, IMREAD_COLOR);
    namedWindow( "Image");
	imshow("Image", img);
	 
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    cout<<"Channels in img:\t"<<img.channels()<<endl;
	cout<<"Channels in img_gray:\t"<<img_gray.channels()<<endl;
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
	cvtColor(img, img_hsv, COLOR_BGR2HSV); // use CV_BGR... because it's the default channels order in opencv
	cvtColor(img, img_hls, COLOR_BGR2HLS);
	cvtColor(img, img_lab, COLOR_BGR2Lab);
	cvtColor(img, img_luv, COLOR_BGR2Luv);
	cvtColor(img, img_crcb,COLOR_BGR2YCrCb);

	imshow("HSV", img_hsv);
	imshow("HSL", img_hls);
	imshow("Lab", img_lab);
	imshow("Luv", img_luv);
	imshow("CrCb", img_crcb);

    waitKey(0);
    cout<<"Goodbye!"<<endl;

    return 0;
}
