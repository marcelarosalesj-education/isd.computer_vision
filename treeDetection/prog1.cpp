/*
    This program loads some bands of a multispectral image and 
    creates a RGB451 false color image.

    This will help to create the treeDetection App.
*/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace cv;
using namespace std;

int main()
{
	Mat img1, img4, img5, img451, channel[3];
    string file_name = "vegas/vegas-band";
    img4 = imread("./img_in/"+file_name+"4.tif", CV_LOAD_IMAGE_GRAYSCALE);
    img5 = imread("./img_in/"+file_name+"5.tif", CV_LOAD_IMAGE_GRAYSCALE);
    img1 = imread("./img_in/"+file_name+"1.tif", CV_LOAD_IMAGE_GRAYSCALE);

    //namedWindow( "Image", CV_WINDOW_AUTOSIZE );
    imshow("Image 4", img4);
    imshow("Image 5", img5);
    imshow("Image 1", img1);
    cout << "CH : "<<img4.channels()<<endl;
    cout << "CH : "<<img5.channels()<<endl;
    cout << "CH : "<<img1.channels()<<endl;

    /*
        Assigns img1 to Blue channel, img5 to Green channel and img4 to Red channel.
        Then merges the new arrangement into img451.
        The result is correct after comparing with ImageJ software.
    */

    channel[0] = img1; // B
    channel[1] = img5; // G
    channel[2] = img4; // R
    merge(channel,3,img451);

    cout << "CH : "<<img451.channels()<<endl;
    imshow("Image 451", img451);

    waitKey(0);
    cout<<"Goodbye!"<<endl;

    return 0;
}