#include "Functions.hpp"

int main() {
    cout << "DPW QuadTree Compression Program" << endl;
    cout << "--------------------------------" << endl;
    cout << "Enter the absolute image path: ";
    string path;
    cin >> path;
    Mat image = imread(path);
    if (image.empty()) {
        cerr << "Error: Could not open or find the image!" << endl;
        return -1;
    }
    Mat imageRGB;
    cvtColor(image, imageRGB, COLOR_BGR2RGB);
    cout << "Image loaded successfully!" << endl;
    cout << "Pick a compression method:" << endl;
    cout << "1. QuadTree Compression with Variance" << endl;
    cout << "2. QuadTree Compression with Mean Absolute Deviation" << endl;
    cout << "3. QuadTree Compression with Max Pixel Difference" << endl;
    cout << "4. QuadTree Compression with Entropy" << endl;
    cout << "Enter a compression method (1-4): ";
    int method;
    try {
        cin >> method;
        if (method < 1 || method > 4) {
            throw invalid_argument("Invalid method number. Please enter a number between 1 and 4.");
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    cout << "Treshold value: ";
    double threshold;
    try {
        cin >> threshold;
        if (threshold < 0) {
            throw invalid_argument("Threshold value must be non-negative.");
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    cout << "Minimum block size: ";
    int minBlockSize;
    try {
        cin >> minBlockSize;
        if (minBlockSize <= 0) {
            throw invalid_argument("Minimum block size must be positive.");
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    cout << "Compression ratio: ";
    double compressionRatio;
    try {
        cin >> compressionRatio;
        if (compressionRatio <= 0) {
            throw invalid_argument("Compression ratio must be positive.");
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    string outputPath = path;
    cout << "Enter the absolute output path: ";
    cin >> outputPath;
    

    double timeStart = (double)getTickCount();
    // Process the image using the selected method
    Functions functions;
    Mat compressedImage = functions.CheckFunction(method, imageRGB, threshold, minBlockSize);
    if (compressedImage.empty()) {
        cerr << "Error: Compression failed!" << endl;
        return -1;
    }
    double timeEnd = (double)getTickCount();
    double timeElapsed = (timeEnd - timeStart) / getTickFrequency();
    cout << "Time elapsed: " << timeElapsed << " seconds" << endl;
    double initialSize = (double) image.total() * image.elemSize();
    cout << "Initial image size: " << initialSize / 1024 << " KB" << endl;
    double compressedSize = (double) compressedImage.total() * compressedImage.elemSize();
    cout << "Compressed image size: " << compressedSize / 1024 << " KB" << endl;
    double cr = functions.CalcCompressionRatio(imageRGB, compressedImage);
    cout << "Compression ratio: " << cr << endl;
    imshow("Converted Image (RGB)", imageRGB);
    waitKey(0);
    return 0;
}