#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    // Load the image
    Mat image = imread("test/ferrari.jpeg", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }
    //DIsplay the image
    imshow("Original Image", image);
    waitKey(0);
}