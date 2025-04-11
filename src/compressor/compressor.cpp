#include "compressor.hpp"

// Compressor::Compressor(const Image& image, const std::string& outputPath, const std::string& gifPath,
//                        double threshold, int minBlockSize, double targetCompression, const EMM& errorMethod)
//     : outputPath(outputPath), gifPath(gifPath), targetCompression(targetCompression), errorMethod(errorMethod), inputImage(image),
//       outputImage(image), originalSize(image.getFileSize()), animation(gifPath.empty() ? nullptr : new Animation(gifPath, image.getWidth(), image.getHeight())),
//       quadtree(inputImage, errorMethod, threshold, minBlockSize, animation) { }

Compressor::Compressor(const Image& image, const std::string& outputPath, const std::string& gifPath, double threshold, int minBlockSize, double targetCompression, const EMM& errorMethod)
        : outputPath(outputPath), gifPath(gifPath), targetCompression(targetCompression), errorMethod(errorMethod), inputImage(image),
          outputImage(image), originalSize(image.getFileSize()), animation(nullptr),
          quadtree(inputImage, errorMethod, threshold, minBlockSize) { }

Compressor::~Compressor() {
    if (animation != nullptr) {
        delete animation;
        animation = nullptr;
    }
}

void Compressor::compress() {
    timeStart = clock();
    if (targetCompression != 0) {
        targetCompress();
    }
    quadtree.construct();
    // if (animation != nullptr) {
    //     quadtree.generateAnimation();
    // }
    quadtree.render(outputImage);
    outputImage.save(outputPath);
    if (!gifPath.empty()) {
        quadtree.generateAnimation(gifPath);
    }
    outputImage.setFileSize(outputImage.estimateNewFileSize());
    timeEnd = clock();
}

void Compressor::targetCompress() {
    double leftBound, rightBound;
    if (errorMethod.identify() == "SSIM") {
        leftBound = errorMethod.getUpperBound();
        rightBound = errorMethod.getLowerBound();
    } else {
        leftBound = errorMethod.getLowerBound();
        rightBound = errorMethod.getUpperBound();
    }

    double targetSize = originalSize * (1 - targetCompression);
    quadtree.setThreshold(leftBound);
    quadtree.construct();
    quadtree.render(outputImage);
    outputImage.setFileSize(outputImage.estimateNewFileSize());
    if (outputImage.getFileSize() < targetSize) {
        quadtree.setThreshold(leftBound);
        return;
    }

    quadtree.setThreshold(rightBound);
    quadtree.construct();
    quadtree.render(outputImage);
    outputImage.setFileSize(outputImage.estimateNewFileSize());
    if (outputImage.getFileSize() > targetSize) {
        quadtree.setThreshold(rightBound);
        return;
    }
    double bestError = std::numeric_limits<double>::max();
    double bestThreshold = quadtree.getThreshold();

    for (int i = 0; i < 30; i++) {
        double mid = (leftBound + rightBound) / 2;
        quadtree.setThreshold(mid);
        quadtree.construct();
        quadtree.render(outputImage);
        outputImage.setFileSize(outputImage.estimateNewFileSize());
        double currentSize = outputImage.getFileSize();
        double currentError = std::abs(currentSize - targetSize);

        if (currentError < bestError) {
            bestError = currentError;
            bestThreshold = mid;
        }

        if (currentSize > targetSize) {
            leftBound = mid;
        } else {
            rightBound = mid;
        }

        if (currentError / targetSize < 0.0001) {
            break;
        }
    }
    quadtree.setThreshold(bestThreshold);
}
