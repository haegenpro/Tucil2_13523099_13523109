#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class IOHandler {
    private:
        string filePath;
        Mat imageRGB;
        Mat imageGray;
        int method;
        double threshold;
        int minBlockSize;
        Mat compressedImage;
    public:
        
};