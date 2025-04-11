#include "quadtree/quadtree.hpp"
#include "error_measurement/mad.hpp"
#include "error_measurement/mpd.hpp"
#include "error_measurement/variance.hpp"
#include "error_measurement/entropy.hpp"
#include "error_measurement/ssim.hpp"
#include "compressor/compressor.hpp"
#include <regex>

using namespace std;

int main() {
    string inputFilePath, outputFilePath, gifFilePath;
    double threshold;
    int minBlockSize;
    double targetCompression;
    int method;
    string ext;

    Image* inputImage = nullptr;

    auto trim = [](std::string& s) {
        s = std::regex_replace(s, std::regex("^\\s+|\\s+$"), "");
    };

    while (true) {
        cout << "Enter input file path: ";
        getline(cin, inputFilePath);
        trim(inputFilePath);
    
        ext = fs::path(inputFilePath).extension().string();
        if (ext != ".png" && ext != ".jpg" && ext != ".jpeg") {
            cerr << "Error: Unsupported input file extension. Only .png, .jpg, and .jpeg are allowed.\n";
            continue;
        }
    
        Image* temp = new Image(inputFilePath);
        if (temp->getData() == nullptr) {
            delete temp;
            continue;
        }
    
        inputImage = temp;
        break;
    }
    

    cout << "1. QuadTree Compression with Mean Absolute Deviation" << endl;
    cout << "2. QuadTree Compression with Max Pixel Difference" << endl;
    cout << "3. QuadTree Compression with Variance" << endl;
    cout << "4. QuadTree Compression with Entropy" << endl;
    cout << "5. QuadTree Compression with Structural Similarity Index" << endl;

    while (true) {
        cout << "Enter a compression method (1-5): ";
        cin >> method;
        if (!cin.fail() && method >= 1 && method <= 5) break;

        cerr << "Error: Invalid method number. Please enter a number between 1 and 5.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    EMM* errorMethod = nullptr;
    switch (method) {
        case 2: errorMethod = new MPD(); break;
        case 3: errorMethod = new Variance(); break;
        case 4: errorMethod = new Entropy(); break;
        case 5: errorMethod = new SSIM(); break;
        default: errorMethod = new MAD(); break;
    }

    while (true) {
        cout << "Enter threshold [" << errorMethod->getLowerBound() << " - " << errorMethod->getUpperBound() << "]: ";
        cin >> threshold;

        if (!cin.fail() && errorMethod->ThresholdWithinBound(threshold)) break;

        cerr << "Error: Threshold must be within the valid range for this error metric.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Enter minimum block size: ";
        cin >> minBlockSize;
        if (!cin.fail() && minBlockSize > 0) break;

        cerr << "Error: Minimum block size must be positive.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Enter target compression ratio [0.0 - 1.0]: ";
        cin >> targetCompression;
        if (!cin.fail() && targetCompression >= 0 && targetCompression <= 1) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        cerr << "Error: Compression ratio must be between 0 and 1.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Enter output file path: ";
        getline(cin, outputFilePath);
        trim(outputFilePath);
    
        fs::path outputExt = fs::path(outputFilePath).extension();
        fs::path outputDir = fs::path(outputFilePath).parent_path();
    
        if (outputExt != ".png" && outputExt != ".jpg" && outputExt != ".jpeg") {
            cerr << "Error: Unsupported output file extension. Only .png, .jpg, and .jpeg are allowed.\n";
            continue;
        }
    
        if (outputExt != ext) {
            cerr << "Error: Output file extension must match the input file extension (" << ext << ").\n";
            continue;
        }
    
        if (!outputDir.empty() && !fs::exists(outputDir)) {
            cerr << "Error: Output directory does not exist: " << outputDir << endl;
            continue;
        }
    
        break;
    }
    
    while (true) {
        cout << "Enter GIF file path (or leave blank): ";
        getline(cin, gifFilePath);
        trim(gifFilePath);
    
        if (gifFilePath.empty()) break;
    
        if (fs::path(gifFilePath).extension() != ".gif") {
            cerr << "Error: GIF path must end with '.gif'.\n";
            continue;
        }
    
        fs::path gifDir = fs::path(gifFilePath).parent_path();
        if (!gifDir.empty() && !fs::exists(gifDir)) {
            cerr << "Error: GIF output directory does not exist: " << gifDir << endl;
            continue;
        }
    
        break;
    }
    
    Compressor compressor(*inputImage, outputFilePath, gifFilePath, threshold, minBlockSize, targetCompression, *errorMethod);
    compressor.compress();

    double timeElapsed = (compressor.timeEnd - compressor.timeStart) / CLOCKS_PER_SEC;
    cout << "Time taken for compression: " << timeElapsed << " seconds" << endl;
    cout << "Initial image size: " << compressor.inputImage.getFileSize() << " bytes" << endl;
    cout << "Compressed image size: " << compressor.outputImage.getFileSize() << " bytes" << endl;
    if (compressor.originalSize == 0) {
        cout << "Compression percentage: N/A (original size is 0)" << endl;
    } else {
        double ratio = static_cast<double>(compressor.outputImage.getFileSize()) / compressor.originalSize;
        cout << "Compression percentage: " << (1.0 - ratio) * 100 << "%" << endl;
    }
    cout << "Depth of QuadTree: " << compressor.quadtree.getDepth() << endl;
    cout << "Total nodes: " << compressor.quadtree.getTotalNodes() << endl;
    cout << "Image saved to: " << compressor.outputPath << endl;
    if (compressor.animation != nullptr) {
        cout << "GIF saved to: " << compressor.gifPath << endl;
    }

    delete errorMethod;
    delete inputImage;
    return 0;
}
