#include "quadtree/quadtree.hpp"
#include "error_measurement/mad.hpp"
#include "error_measurement/mpd.hpp"
#include "error_measurement/variance.hpp"
#include "error_measurement/entropy.hpp"

using namespace std;

int main() {
    string inputFilePath, outputFilePath;
    double threshold;
    int minBlockSize;

    cout << "Enter input file path: ";
    cin >> inputFilePath;
    Image inputImage(inputFilePath);
    if (!inputImage.load(inputFilePath)) {
        cerr << "Error loading image: " << inputFilePath << endl;
        return 1;
    }

    cout << "1. QuadTree Compression with Mean Absolute Deviation" << endl;
    cout << "2. QuadTree Compression with Max Pixel Difference" << endl;
    cout << "3. QuadTree Compression with Variance" << endl;
    cout << "4. QuadTree Compression with Entropy" << endl;
    cout << "Enter a compression method (1-4): ";
    int method;
    cin >> method;
    if (cin.fail() || method < 1 || method > 4) {
        cerr << "Error: Invalid method number. Please enter a number between 1 and 4." << endl;
        return -1;
    }

    EMM* errorMethod = nullptr;
    switch(method) {
        case 1:
            errorMethod = new MAD();
            break;
        case 2:
            errorMethod = new MPD();
            break;
        case 3:
            errorMethod = new Variance();
            break;
        case 4:
            errorMethod = new Entropy();
            break;
        default:
            errorMethod = new MAD();
            break;
    }

    cout << "Enter threshold: ";
    cin >> threshold;
    if (cin.fail() || threshold < 0) {
        cerr << "Error: Threshold value must be non-negative." << endl;
        delete errorMethod;
        return -1;
    }

    cout << "Enter minimum block size: ";
    cin >> minBlockSize;
    if (cin.fail() || minBlockSize <= 0) {
        cerr << "Error: Minimum block size must be positive." << endl;
        delete errorMethod;
        return -1;
    }

    cout << "Enter compression ratio: ";
    double compressionRatio;
    cin >> compressionRatio;
    if (cin.fail() || compressionRatio <= 0) {
        cerr << "Error: Compression ratio must be positive." << endl;
        delete errorMethod;
        return -1;
    }

    cout << "Enter output file path: ";
    cin >> outputFilePath;

    QuadTree quadTree(inputImage, *errorMethod, threshold, minBlockSize);
    quadTree.construct();
    Image output = inputImage;
    quadTree.render(output);
    output.save(outputFilePath);
    cout << "Image saved to: " << outputFilePath << endl;

    delete errorMethod;
    return 0;
}
