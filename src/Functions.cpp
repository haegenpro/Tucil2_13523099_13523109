#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Functions {
    private:
        double CalcVariance(const Mat& image) { 
            double mean = 0.0; 
            double variance = 0.0; 
            int count = 0;
            // Calculate the mean intensity over the entire image
            for (int i = 0; i < image.rows; ++i) {
                for (int j = 0; j < image.cols; ++j) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    double intensity = (pixel[0] + pixel[1] + pixel[2]) / 3.0;
                    mean += intensity;
                    count++;
                }
            }
            mean /= count;
            // Calculate the variance over the entire image
            for (int i = 0; i < image.rows; ++i) {
                for (int j = 0; j < image.cols; ++j) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    double intensity = (pixel[0] + pixel[1] + pixel[2]) / 3.0;
                    variance += (intensity - mean) * (intensity - mean);
                }
            }
            return variance / count;
        }

        double CalcMeanAbsoluteDeviation(const Mat& image) {
            double mean = 0.0;
            double mad = 0.0;
            int count = 0;
            // Calculate the mean intensity over the entire image
            for (int i = 0; i < image.rows; ++i) {
                for (int j = 0; j < image.cols; ++j) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    double intensity = (pixel[0] + pixel[1] + pixel[2]) / 3.0;
                    mean += intensity;
                    count++;
                }
            }
            mean /= count;
            // Calculate the mean absolute deviation over the entire image
            for (int i = 0; i < image.rows; ++i) {
                for (int j = 0; j < image.cols; ++j) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    double intensity = (pixel[0] + pixel[1] + pixel[2]) / 3.0;
                    mad += abs(intensity - mean);
                }
            }
            return mad / count;
        }

        double CalcMaxPixelDifference(const Mat& image) {
            double maxDiff = 0.0, maxR = 0.0, maxG = 0.0, maxB = 0.0;
            Vec3b minPixel = image.at<Vec3b>(0, 0);
            Vec3b maxPixel = image.at<Vec3b>(0, 0);
            // Find the minimum and maximum pixel values in the image
            for (int i = 0; i < image.rows; ++i) {
                for (int j = 0; j < image.cols; ++j) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    if (pixel[0] < minPixel[0]) minPixel[0] = pixel[0];
                    if (pixel[1] < minPixel[1]) minPixel[1] = pixel[1];
                    if (pixel[2] < minPixel[2]) minPixel[2] = pixel[2];
                    if (pixel[0] > maxPixel[0]) maxPixel[0] = pixel[0];
                    if (pixel[1] > maxPixel[1]) maxPixel[1] = pixel[1];
                    if (pixel[2] > maxPixel[2]) maxPixel[2] = pixel[2];
                }
            }
            // Calculate the maximum pixel difference
            maxR = maxPixel[0] - minPixel[0];
            maxG = maxPixel[1] - minPixel[1];
            maxB = maxPixel[2] - minPixel[2];
            maxDiff = max(max(maxR, maxG), maxB);
            return maxDiff;
        }

        double CalcEntropy(const Mat& image) {
            // Create a histogram for the image
            int histSize = 256;
            float range[] = { 0, 256 };
            const float* histRange = { range };
            Mat hist;
            calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange);
            // Normalize the histogram
            hist /= (image.rows * image.cols);
            // Calculate the entropy
            double entropy = 0.0;
            for (int i = 0; i < histSize; ++i) {
                if (hist.at<float>(i) > 0) {
                    entropy -= hist.at<float>(i) * log(hist.at<float>(i));
                }
            }
            return entropy;
        }

        Mat CompressBlock(const Mat& image) {
            Vec3d sumColor(0, 0, 0);
            int count = 0;
            for (int i = 0; i < image.rows; ++i) {
                for (int j = 0; j < image.cols; ++j) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    sumColor[0] += pixel[0];
                    sumColor[1] += pixel[1];
                    sumColor[2] += pixel[2];
                    count++;
                }
            }
            Vec3b avgColor(sumColor[0] / count, sumColor[1] / count, sumColor[2] / count);
            Mat compressedImage(image.size(), image.type(), avgColor);
            return compressedImage;
        }

        bool CheckBlockSize(int cols, int rows, int minBlockSize) {
            return ((cols * rows) >= minBlockSize);
        }

    public:

        Mat CheckFunction(int method, const Mat& image, double threshold, int minBlockSize) {
        double error = 0.0;
        switch (method) {
            case 1:
                error = CalcVariance(image);
                break;
            case 2:
                error = CalcMeanAbsoluteDeviation(image);
                break;
            case 3:
                error = CalcMaxPixelDifference(image);
                break;
            case 4:
                error = CalcEntropy(image);
                break;
            default:
                cerr << "Error: Invalid method number!" << endl;
                return image;
        }
        // Check if the error is below the threshold and that the block is large enough to be compressed.
        bool isCompressed = (error < threshold) && CheckBlockSize(image.cols, image.rows, minBlockSize);
        if (isCompressed) {
            return CompressBlock(image);
        } 
        else {
            // If the error is above threshold and we can subdivide further, divide the image into four quadrants.
            if (CheckBlockSize(image.cols/2, image.rows/2, minBlockSize)) {
                int midRow = image.rows / 2;
                int midCol = image.cols / 2;
                
                Mat topLeft = CheckFunction(method, image(Rect(0, 0, midCol, midRow)), threshold, minBlockSize);
                Mat topRight = CheckFunction(method, image(Rect(midCol, 0, image.cols - midCol, midRow)), threshold, minBlockSize);
                Mat bottomLeft = CheckFunction(method, image(Rect(0, midRow, midCol, image.rows - midRow)), threshold, minBlockSize);
                Mat bottomRight = CheckFunction(method, image(Rect(midCol, midRow, image.cols - midCol, image.rows - midRow)), threshold, minBlockSize);
                
                Mat top, bottom, combined;
                hconcat(topLeft, topRight, top);
                hconcat(bottomLeft, bottomRight, bottom);
                vconcat(top, bottom, combined);
                return combined;
            } 
            else {
                return CompressBlock(image);
            }
        }
    }    
};