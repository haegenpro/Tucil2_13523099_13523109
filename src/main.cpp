#include "Functions.cpp"

int main() {
    cout << "DPW QuadTree Compression Program" << endl << "--------------------------------" << endl << "Pick a compression method:" << endl;
    cout << "1. QuadTree Compression with Variance" << endl;
    cout << "2. QuadTree Compression with Mean Absolute Deviation" << endl;
    cout << "3. QuadTree Compression with Max Pixel Difference" << endl;
    cout << "4. QuadTree Compression with Entropy" << endl;
    cout << "Insert a compression method (1-4): ";
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
    cout << "Insert treshold value: ";
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
    cout << "Insert the minimum block size: ";
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
    cout << "Insert the image path for compression: ";
    string path;
    cin >> path;
    Mat image = imread(path);
    if (image.empty()) {
        cerr << "Error: Could not open or find the image!" << endl;
        return -1;
    }
    // Convert the image from BGR to RGB
    Mat imageRGB;
    cvtColor(image, imageRGB, COLOR_BGR2RGB);

    // Example: Access and print the RGB values of the pixel at (0,0)
    Vec3b pixel = imageRGB.at<Vec3b>(0, 0);
    cout << "Pixel at (0,0): R = " << static_cast<int>(pixel[0])
            << ", G = " << static_cast<int>(pixel[1])
            << ", B = " << static_cast<int>(pixel[2]) << endl;

    imshow("Original Image (BGR)", image);
    imshow("Converted Image (RGB)", imageRGB);

    waitKey(0);
    return 0;
}