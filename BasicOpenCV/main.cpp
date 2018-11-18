#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <experimental/filesystem>

using namespace std;
using namespace cv;
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

int main(void)
{
    // Variables
    int opt;
    bool selection = false;
    Mat img;

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
    img = imread(file_name);
    namedWindow( "Image");
	imshow("Image", img);

	waitKey(0);
    cout<<"Goodbye!"<<endl;

    return 0;
}
