/*
    This program shows trees.


    Canny Detector
    http://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/canny_detector/canny_detector.html


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


Mat img, src_gray;
Mat dst, detected_edges;
Mat img_hsv, blur_bgr, blur_hsv;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;

int Px;
int Py;
int vR;
int vG;
int vB;
float rpi;
float gpi;
float bpi;
float vH;
float vS;
float vV;
float Cmax;
float Cmin;
float dif;
Mat imagenClick;


void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     uchar* destination;
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Left button (" << x << ", " << y << ")" << endl;
          Px=x;
          Py=y;
          destination = (uchar*) img.ptr<uchar>(Py);
            
          vB=destination[Px * 3];
          vG=destination[Px*3+1];
          vR=destination[Px*3+2];
          cout << "1) RGB " << vR << " "<< vG <<" "<<vB<< endl;
          //Valores HSV
          rpi = vR / 255.0;
          gpi = vG / 255.0;
          bpi = vB / 255.0;

          Cmax = max(rpi, gpi);
          Cmax = max(Cmax, bpi);
          Cmin = min(rpi, gpi);
          Cmin = min(Cmin, bpi);
          dif = Cmax - Cmin;
          if(dif == 0){
              vH=0;
          } else if(Cmax == rpi){
              vH = 60.0 * (fmod(((gpi-bpi)/dif),6.0));
          } else if(Cmax == gpi){
              vH = 60.0 * (((bpi-rpi)/dif)+2.0);
          } else if(Cmax == bpi){
              vH = 60.0 * (((rpi-gpi)/dif)+4.0);
          }
          if(vH<0){
              vH=360+vH;
          }
          if(Cmax==0){
              vS = 0;
          } else {
              vS = dif/Cmax;
          }
          vV = Cmax;  
          cout <<"2) HSV(or)"<< (vH)*float(180/360) << "  " << (vS)*float(100/255) << "  " << (vV)*float(100/255) << endl;
          cout <<"   HSV(cv)"<< (vH) << "  " << (vS) << "  " << (vV) << endl;
     }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
          cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
          cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
}


/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  img.copyTo( dst, detected_edges);
  imshow( "Edge Map", dst );
 }


int main()
{
	bool goahead=true;
	while( goahead ){
		string aux;
		cout << "Which photo (number from 000 to 261)?"<< endl;
		cin >> aux;
		// Load photo
	    string file_name = "DJI_0"+aux+".jpg";
	    cout << file_name<<endl;
	    img = imread("./Photos/"+file_name, CV_LOAD_IMAGE_COLOR);

	    // Resize
	    Size size(img.cols/10.0, img.rows/10.0);
	    resize(img, img, size);

	    namedWindow("Image", CV_WINDOW_AUTOSIZE);
	    setMouseCallback("Image", CallBackFunc, NULL);
	    imshow("Image", img);

	    cout << "Rows: " << img.rows << endl;
	    cout << "Cols: " << img.cols << endl;

	    // Gaussian 3x3 filter
	    Mat my_kernel;
	    int kernel_size;
	    kernel_size=3;
	    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
	            0.077847,0.123317,0.077847,0.123317,0.195346,0.123317,0.077847,0.123317,0.077847 // Gauss 3x3
	    );
	    filter2D(img, blur_bgr, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
	    
	    namedWindow("Gauss 3x3 BGR", CV_WINDOW_AUTOSIZE);
	    setMouseCallback("Gauss 3x3 BGR", CallBackFunc, NULL);
	    imshow("Gauss 3x3 BGR", blur_bgr);
	    
	    // Filter green in BGR color space.
	    Mat green_bgr_filtered;
	    //inRange(blur_bgr, Scalar(10,40,10) , Scalar(60,140,60) ,  green_bgr_filtered); // works
	    inRange(blur_bgr, Scalar(30,30,20) , Scalar(150,170,90) ,  green_bgr_filtered); // works better
	    threshold(green_bgr_filtered, green_bgr_filtered, 10,255,THRESH_BINARY_INV);
	    namedWindow("Green filter BGR", CV_WINDOW_AUTOSIZE);
	    imshow("Green filter BGR", green_bgr_filtered);
	    //erode(green_bgr_filtered, green_bgr_filtered, my_kernel, Point(-1, -1), 2, 1, 1);
	    //imshow("Green filter BGR Erode ",green_bgr_filtered);



	    // Get image in HSV color space
	    cvtColor(img, img_hsv, CV_BGR2HSV);
	    namedWindow("Image HSV");
	    setMouseCallback("Image HSV", CallBackFunc, NULL);
	    imshow("Image HSV", img_hsv);

	    // Gaussian 3x3 filter HSV
	    filter2D(img_hsv, blur_hsv, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
	    setMouseCallback("Gauss 3x3 HSV", CallBackFunc, NULL);
	    imshow("Gauss 3x3 HSV", blur_hsv);

	    // Filter green in HSV color space.
	    Mat green_hsv_filtered;
	    double Hmax, Hmin, Smax, Smin, Vmax, Vmin;    
	    // HSV original values
	    Hmax = 100.0;
	    Smax = 80.00;
	    Vmax = 70.0;

	    Hmin = 60.42;  
	    Smin = 35.00;
	    Vmin = 15.00;
	    // HSV openCV values
	    Hmax = Hmax*(180.0/360);
	    Hmin = Hmin*(180.0/360);
	    Smin = Smin*(255.0/100);
	    Smax = Smax*(255.0/100);
	    Vmax = Vmax*(255.0/100);
	    Vmin = Vmin*(255.0/100);

	    cout << "Filtered HSV max : "<<Hmax<<" , "<<Smax<<" , "<<Vmax<< endl;
	    cout << "Filtered HSV min : "<<Hmin<<" , "<<Smin<<" , "<<Vmin<< endl;
	    inRange(blur_hsv, Scalar(Hmin, Smin, Vmin) , Scalar(Hmax, Smax, Vmax) ,  green_hsv_filtered);
	    threshold(green_hsv_filtered, green_hsv_filtered, 10,255,THRESH_BINARY_INV);
	    namedWindow("Green filter HSV", CV_WINDOW_AUTOSIZE);
	    imshow("Green filter HSV", green_hsv_filtered);

		/*
	    // Canny 

	    //img = green_bgr_filtered;

	    /// Create a matrix of the same type and size as src (for dst)
	    dst.create( img.size(), img.type() );

	    /// Convert the image to grayscale
	    cvtColor( img, src_gray, CV_BGR2GRAY );

	    /// Create a window
	    namedWindow( "Edge Map", CV_WINDOW_AUTOSIZE );

	    /// Create a Trackbar for user to enter threshold
	    createTrackbar( "Min Threshold:", "Edge Map", &lowThreshold, max_lowThreshold, CannyThreshold );

	    /// Show the image
	    CannyThreshold(0, 0);
	    */
	    
	    waitKey(0);
	    destroyAllWindows();

	    
	    /*cout << "Continue? (y)" << endl;
	    cin >> aux;
	    if(aux != "y"){
	    	/goahead = false;
	    }*/
	    

	}
    

    cout<<"Goodbye!"<<endl;

    return 0;
}