#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Functions {
    public:
        Mat Compress(const Mat& image, int x, int y, int size) {
            // Check if the region is within the image bounds
            if (x < 0 || y < 0 || x + size > image.rows || y + size > image.cols) {
                cerr << "Error: Region out of bounds!" << endl;
                return Mat();
            }

            // Calculate the average color of the region
            Vec3b avgColor = AverageColor(image, x, y, size);

            // Create a new image with the same size as the original
            Mat compressedImage = Mat::zeros(image.size(), image.type());

            // Fill the region with the average color
            for (int i = x; i < x + size; ++i) {
                for (int j = y; j < y + size; ++j) {
                    compressedImage.at<Vec3b>(i, j) = avgColor;
                }
            }

            return compressedImage;
        }
        double Variance(const Mat& image, int x, int y, int size) {
            double mean = 0.0;
            double variance = 0.0;
            int count = 0;

            for (int i = x; i < x + size; ++i) {
                for (int j = y; j < y + size; ++j) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    mean += (pixel[0] + pixel[1] + pixel[2]) / 3.0;
                    count++;
                }
            }

            mean /= count;

            for (int i = x; i < x + size; ++i) {
                for (int j = y; j < y + size; ++j) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    double intensity = (pixel[0] + pixel[1] + pixel[2]) / 3.0;
                    variance += (intensity - mean) * (intensity - mean);
                }
            }

            return variance / count;
        }
        Vec3b AverageColor(const Mat& image, int x, int y, int size) {
            Vec3b sumColor = Vec3b(0, 0, 0);
            int count = 0;

            for (int i = x; i < x + size; ++i) {
                for (int j = y; j < y + size; ++j) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    sumColor[0] += pixel[0];
                    sumColor[1] += pixel[1];
                    sumColor[2] += pixel[2];
                    count++;
                }
            }

            return Vec3b(sumColor[0] / count, sumColor[1] / count, sumColor[2] / count);
        }
};