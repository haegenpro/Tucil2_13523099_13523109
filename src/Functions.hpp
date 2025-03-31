#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

class Functions{
    public:
        double CalcVariance(const Mat& image);
        double CalcMeanAbsoluteDeviation(const Mat& image);
        double CalcMaxPixelDifference(const Mat& image);
        double CalcEntropy(const Mat& image);
        Mat CompressBlock(const Mat& image);
        bool CheckBlockSize(int cols, int rows, int minBlockSize);
        double CalcCompressionRatio(const Mat& original, const Mat& compressed);
        Mat CheckFunction(int method, const Mat& image, double threshold, int minBlockSize);
};

#endif // FUNCTIONS_HPP