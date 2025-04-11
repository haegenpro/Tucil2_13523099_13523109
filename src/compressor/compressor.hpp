#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

#include "../error_measurement/emm.hpp"
#include "../image/animation.hpp"
#include "../image/image.hpp"
#include "../quadtree/quadtree.hpp"
#include "../quadtree/node.hpp"
#include <string>
#include <cmath>

class Compressor {
public:
    std::string outputPath;
    std::string gifPath;
    double targetCompression;

    const EMM& errorMethod;
    Image inputImage;
    Image outputImage;
    Animation* animation = nullptr;
    uintmax_t originalSize;
    QuadTree quadtree;

    double timeStart;
    double timeEnd;

    double bestThreshold;

    Compressor(const Image& image, const std::string& outputPath, const std::string& gifPath, double threshold, int minBlockSize, double targetCompression, const EMM& errorMethod);
    ~Compressor();
    void compress();
    void targetCompress();
};

#endif