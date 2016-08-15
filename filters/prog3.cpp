/*
From this tutorial
http://www.learnopencv.com/applycolormap-for-pseudocoloring-in-opencv-c-python/


From this
http://stackoverflow.com/questions/13981699/opencv-how-does-the-filter2d-method-actually-work
I understood how to apply a kernel to an image

So cool!
http://docs.gimp.org/es/plug-in-convmatrix.html
try it!

*/
//#include <opencv2/contrib/contrib.hpp> // had to remove for opencv3
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp" // I added this to make it work with opencv3
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int main()
{
	Mat img, dst, dst1, my_kernel;
	string file_name;
    int kernel_size;

	cout<<"Which image?"<<endl;
	cin>>file_name;
    //file_name="imagen1";
    img = imread("./img_in/"+file_name+".jpg",CV_LOAD_IMAGE_COLOR);

    
    // Move this depending on image size
    cout << " cols "<< img.cols << endl;
    cout << " rows "<< img.rows << endl;
    Size size(img.cols/7,img.rows/7);//the dst image size,e.g.100x100
    resize(img,img,size);//resize image

    //namedWindow("IMG", WINDOW_NORMAL);
    imshow("IMG", img);


    //
    kernel_size=3;
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                //0.111,0.111,0.111,0.111,0.111,0.111,0.111,0.111,0.111 // Promediador 3x3
                0.077847,0.123317,0.077847,0.123317,0.195346,0.123317,0.077847,0.123317,0.077847 // Gauss 3x3
                //-1,-1,-1,-1,8,-1,-1,-1,-1 // Laplaciano
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("DST",dst);
    dst=dst-img;
    imshow("Experimento 1", dst);
    

    //
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                -1,-1,-1,-1,8,-1,-1,-1,-1 // Laplaciano
    );
    filter2D(dst, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Experimento 2", dst);


    // It looks cool, but idk what it is
    //my_kernel = (Mat_<double>(kernel_size,kernel_size) << -1, -1, -1, -1, 9, -1, -1, -1, -1);

    kernel_size=5;
    //Gaussian Kernel 5x5, Sigma=1
    // this was calculated using http://dev.theomader.com/gaussian-kernel-calculator/
    my_kernel = (Mat_<double>(kernel_size,kernel_size) << 
                0.003765,0.015019,0.023792,0.015019,0.003765,0.015019,0.059912,0.094907,0.059912,0.015019,0.023792,0.094907,0.150342,0.094907,0.023792,0.015019,0.059912,0.094907,0.059912,0.015019,0.003765,0.015019,0.023792,0.015019,0.003765
                );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Gaussian 5x5 Sigma=1", dst);

    // Gaussian Kernel 5x5, Sigma=0.5
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0.000002,0.000212,0.000922,0.000212,0.000002,0.000212,0.024745,0.107391,0.024745,0.000212,0.000922,0.107391,0.466066,0.107391,0.000922,0.000212,0.024745,0.107391,0.024745,0.000212,0.000002,0.000212,0.000922,0.000212,0.000002
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Gaussian 5x5 Sigma=0.5", dst);

    // Gaussian Kernel 5x5, Sigma=2.0
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0.023528,0.033969,0.038393,0.033969,0.023528,0.033969,0.049045,0.055432,0.049045,0.033969,0.038393,0.055432,0.062651,0.055432,0.038393,0.033969,0.049045,0.055432,0.049045,0.033969,0.023528,0.033969,0.038393,0.033969,0.023528
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Gaussian 5x5 Sigma=2.0", dst);


    // Gaussian Kernel 3x3, Sigma=1.0
    kernel_size=3;
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0.077847,0.123317,0.077847,0.123317,0.195346,0.123317,0.077847,0.123317,0.077847
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Gaussian 3x3 Sigma=1.0", dst);
    
    // Mean and median filters
    // http://www.markschulze.net/java/meanmed.html

    // Median Filter
    //http://www.bogotobogo.com/OpenCV/opencv_3_tutorial_imgproc_gausian_median_blur_bilateral_filter_image_smoothing_B.php
    medianBlur(img,dst,kernel_size);
    imshow("Filtro Mediano 3x3", dst);

    // Mean Filter 5x5
    //http://dea.unsj.edu.ar/imagenes/recursos/capitulo3.pdf
    // ctrl+f promediador
    kernel_size=5;
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04
    ); // it's 1/25
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Promediador 5x5", dst);
    
    // Mean Filter 3x3
    kernel_size=3;
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0.111,0.111,0.111,0.111,0.111,0.111,0.111,0.111,0.111
    ); // it's 1/9
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Promediador 3x3", dst);

    // Laplaciano
    // http://verona.fi-p.unam.mx/boris/teachingnotes/Capitulo4.pdf
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                -1,-1,-1,-1,8,-1,-1,-1,-1
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Laplacian with diagonals", dst);

    // Laplaciano
    // http://homepages.inf.ed.ac.uk/rbf/HIPR2/unsharp.htm
    // http://ik.itba.edu.ar/~jacoby/Image%20Processing/Teoria/Clase4/Filtros%20v006.pdf
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0,-1,0,-1,4,-1,0,-1,0
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Laplacian without diagonals  ", dst);


    // High boost
    // laplace high boost
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                -1,-1,-1,-1,9.7,-1,-1,-1,-1 // 8+1.7, A=1.7
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    // blur high boost
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0.111,0.111,0.111,0.111,0.111,0.111,0.111,0.111,0.111
    ); // it's 1/9
    filter2D(img, dst1, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    dst=dst-dst1; // laplacian - mean filter
    imshow("High Boost Filter", dst);


    // Unsharp Filter
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                -1,-1,-1,-1,8,-1,-1,-1,-1
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    dst=-dst+img; // - laplacian + image
    imshow("Unsharp Filter", dst);


    // LOG Filter
    // Gaussian Kernel 3x3, Sigma=1.0
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0.077847,0.123317,0.077847,0.123317,0.195346,0.123317,0.077847,0.123317,0.077847
    );
    filter2D(img, dst1, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                -1,-1,-1,-1,8,-1,-1,-1
    );
    filter2D(dst1, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("LOG Filter", dst);


    //  -- Border Detection
    // Prewitt Filter
    // http://verona.fi-p.unam.mx/boris/teachingnotes/Capitulo4.pdf - de aqui saque el prewitt y sobel
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                1,0,-1,1,0,-1,1,0,-1
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Prewitt in X", dst);

    // Sobel Filter
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                1,0,-1,2,0,-2,1,0,-1
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Sobel in X", dst);

    // Prewitt Filter
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                1,1,1,0,0,0,-1,-1,-1
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Prewitt in Y", dst);

    // Sobel Filter
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                1,2,1,0,0,0,-1,-2,-1
    );
    filter2D(img, dst, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Sobel in Y", dst);
    
    // Erosion
    kernel_size=3;
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                1,1,1,1,1,1,1,1,1
    );
    erode(img, dst, my_kernel, Point(-1, -1), 2, 1, 1);
    imshow("Erosión", dst);
    // Dilatate
    dilate(img, dst, my_kernel, Point(-1, -1), 2, 1, 1);
    imshow("Dilatación", dst);

    // Apertura
    erode(img, dst, my_kernel, Point(-1, -1), 2, 1, 1);
    dilate(dst, dst, my_kernel, Point(-1, -1), 2, 1, 1);
    imshow("Apertura", dst);

    // Cerradura
    dilate(img, dst, my_kernel, Point(-1, -1), 2, 1, 1);
    erode(dst, dst, my_kernel, Point(-1, -1), 2, 1, 1);
    imshow("Cerradura", dst);

    
    /* 
        I don't know if this works
    */
    Mat dst2,dst3,dst4;
    // Detector de esquinas
    kernel_size=3;
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                //0,1,0,1,1,1,0,1,0
                0,1,0,0,1,1,0,0,0 // deteccion de esquinas L

    );
    filter2D(img, dst1, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0,1,0,1,1,0,0,0,0
    );
    filter2D(img, dst2, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0,0,0,1,1,0,0,1,0
    );
    filter2D(img, dst3, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0,0,0,0,1,1,0,1,0
    );
    filter2D(img, dst4, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );

    dst=dst1|dst2|dst3|dst4;
    imshow("Esquinas", dst);


    my_kernel= (Mat_<double>(kernel_size,kernel_size) <<
                0,-1,0,-1,4,-1,0,-1,0
    );
    //my_kernel=cv::flip(my_kernel);
    Point anchor;
    anchor = Point( -1, -1 );
    //filter2D(img,  dst1, my_kernel,Point(my_kernel.cols - anchor.x - 1, my_kernel.rows - anchor.y - 1),0, BORDER_DEFAULT);
    //filter2D(dst1, dst2, my_kernel,Point(my_kernel.cols - anchor.x - 1, my_kernel.rows - anchor.y - 1),0, BORDER_DEFAULT);
    filter2D(img, dst1, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    filter2D(dst1, dst2, -1 , my_kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );
    imshow("Canny?", dst2);




    waitKey(0);
    cout<<"Goodbye!"<<endl;

    return 0;
}