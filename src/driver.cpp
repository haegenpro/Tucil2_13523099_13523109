#include "../quadtree/quadtree.hpp"
#include "error_measurement/mad.hpp"
#include "error_measurement/mpd.hpp"
#include "error_measurement/variance.hpp"
#include "error_measurement/entropy.hpp"

using namespace std;

int main(){
    cin >> noskipws;
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
    try {
        cin >> method;
        if (method < 1 || method > 4) {
            throw invalid_argument("Invalid method number. Please enter a number between 1 and 4.");
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
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
    cout << "Enter threshold:";
    cin >> threshold;
    try {
        cin >> threshold;
        if (threshold < 0) {
            throw invalid_argument("Threshold value must be non-negative.");
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    cout << "Enter minimum block size:";
    cin >> minBlockSize;
    try {
        cin >> minBlockSize;
        if (minBlockSize <= 0) {
            throw invalid_argument("Minimum block size must be positive.");
        }
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    cout << "Enter compression ratio: ";
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
    cout << "Enter output file path: " << endl;
    QuadTree quadTree(inputImage, *errorMethod, threshold, minBlockSize);

    quadTree.construct();
    Image output = inputImage;
    quadTree.render(output);
    output.save(outputFilePath);
    cout << "Image saved to: " << outputFilePath << endl;
}