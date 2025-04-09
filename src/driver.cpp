#include "quadtree/quadtree.hpp"
#include "error_measurement/mad.hpp"
#include "error_measurement/mpd.hpp"
#include "error_measurement/variance.hpp"
#include "error_measurement/entropy.hpp"
#include "error_measurement/ssim.hpp"

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
    cout << "Enter compression ratio: ";
    double compressionRatio;
    cin >> compressionRatio;
    if (cin.fail() || compressionRatio < 0 || compressionRatio > 1) {
        cerr << "Error: Compression ratio must be positive." << endl;
        delete errorMethod;
        return -1;
    }
    cout << "Enter output file path: ";
    cin >> outputFilePath;
    cout << "Enter GIF file path: ";
    cin >> gifFilePath;
    double timeStart = clock();
    Animation gif(gifFilePath, inputImage.getWidth(), inputImage.getHeight());
    Image output = inputImage;
    QuadTree quadTree(inputImage, *errorMethod, threshold, minBlockSize, &gif);
    quadTree.construct();
    quadTree.generateAnimation();
    quadTree.render(output);
    output.save(outputFilePath);
    double timeEnd = clock();
    double timeElapsed = (timeEnd - timeStart) / CLOCKS_PER_SEC;
    cout << "Time taken for compression: " << timeElapsed << " seconds" << endl;
    cout << "Initial image size: " << inputImage.getFileSize() << " bytes" << endl;
    output.setFileSize(output.estimateNewFileSize());
    cout << "Compressed image size: " << output.getFileSize() << " bytes" << endl;
    cout << "Compression ratio: " << (double)output.getFileSize() / inputImage.getFileSize() * 100 << "%" << endl;
    cout << "Depth of QuadTree: " << quadTree.getDepth() << endl;
    cout << "Total nodes: " << quadTree.getTotalNodes() << endl;
    cout << "Image saved to: " << outputFilePath << endl;
    cout << "GIF saved to: " << gifFilePath << endl;
    delete errorMethod;
    return 0;
}
