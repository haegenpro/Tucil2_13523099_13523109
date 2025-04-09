#include "quadtree/quadtree.hpp"
#include "error_measurement/mad.hpp"
#include "error_measurement/mpd.hpp"
#include "error_measurement/variance.hpp"
#include "error_measurement/entropy.hpp"
#include "error_measurement/ssim.hpp"
#include "compressor/compressor.hpp"

using namespace std;

int main() {
    string inputFilePath, outputFilePath, gifFilePath;
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
    cout << "5. QuadTree Compression with Structural Similarity Index" << endl;
    cout << "Enter a compression method (1-5): ";
    int method;
    cin >> method;
    if (cin.fail() || method < 1 || method > 5) {
        cerr << "Error: Invalid method number. Please enter a number between 1 and 5." << endl;
        return -1;
    }

    EMM* errorMethod = nullptr;
    switch(method) {
        case 2:
            errorMethod = new MPD();
            break;
        case 3:
            errorMethod = new Variance();
            break;
        case 4:
            errorMethod = new Entropy();
            break;
        case 5:
            errorMethod = new SSIM();
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
    cout << "Enter target compression ratio: ";
    double targetCompression;
    cin >> targetCompression;
    if (cin.fail() || targetCompression < 0 || targetCompression > 1) {
        cerr << "Error: Compression ratio must be positive." << endl;
        delete errorMethod;
        return -1;
    }
    cout << "Enter output file path: ";
    cin >> outputFilePath;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter GIF file path: ";
    getline(cin, gifFilePath);

    Compressor compressor(inputImage, outputFilePath, gifFilePath, threshold, minBlockSize, targetCompression, *errorMethod);
    compressor.compress();

    double timeElapsed = (compressor.timeEnd - compressor.timeStart) / CLOCKS_PER_SEC;
    cout << "Time taken for compression: " << timeElapsed << " seconds" << endl;
    cout << "Initial image size: " << compressor.inputImage.getFileSize() << " bytes" << endl;
    cout << "Compressed image size: " << compressor.outputImage.getFileSize() << " bytes" << endl;
    cout << "Compression ratio: " << (double) 1 - compressor.outputImage.getFileSize() / compressor.originalSize * 100 << "%" << endl;
    cout << "Depth of QuadTree: " << compressor.quadtree.getDepth() << endl;
    cout << "Total nodes: " << compressor.quadtree.getTotalNodes() << endl;
    cout << "Image saved to: " << compressor.outputPath << endl;
    if (compressor.animation != nullptr) {
        cout << "GIF saved to: " << compressor.gifPath << endl;
    }
    delete errorMethod;
    return 0;
}
