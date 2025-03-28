#include "Functions.cpp"

int main() {
    cout << "DPW QuadTree Compression Program" << endl;
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