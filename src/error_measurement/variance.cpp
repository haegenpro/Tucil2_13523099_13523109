#include "variance.hpp"

// long long Variance::sumColorBlock(const Image& image, int x, int y, int width, int height, Channel c) const {
//     long long sum = 0;

//     for (int i = x; i < x + width; i++) {
//         for (int j = y; j < y + height; j++) {
//             Pixel p = image.getPixelAt(i, j);
//             switch(c) {
//                 case Channel::RED:
//                     sum += p.getRed();
//                     break;
//                 case Channel::GREEN:
//                     sum += p.getGreen();
//                     break;
//                 case Channel::BLUE:
//                     sum += p.getBlue();
//                     break;
//             }
//         }
//     }
//     return sum;
// }

// long long Variance::sumColorSquaredBlock(const Image& image, int x, int y, int width, int height, Channel c) const {
//     long long sum = 0;

//     for (int i = x; i < x + width; i++) {
//         for (int j = y; j < y + height; j++) {
//             Pixel p = image.getPixelAt(i, j);
//             switch(c) {
//                 case Channel::RED:
//                     sum += p.getRed() * p.getRed();
//                     break;
//                 case Channel::GREEN:
//                     sum += p.getGreen() * p.getGreen();
//                     break;
//                 case Channel::BLUE:
//                     sum += p.getBlue() * p.getBlue();
//                     break;
//             }
//         }
//     }
//     return sum;
// }

double Variance::computeBlockError(const Image& image, int x, int y, int width, int height) const {
    int count = width * height;

    long long sumRed = sumColorBlock(image, x, y, width, height, Channel::RED);
    long long sumGreen = sumColorBlock(image, x, y, width, height, Channel::GREEN);
    long long sumBlue = sumColorBlock(image, x, y, width, height, Channel::BLUE);

    long long sumRedSquared = sumColorSquaredBlock(image, x, y, width, height, Channel::RED);
    long long sumGreenSquared = sumColorSquaredBlock(image, x, y, width, height, Channel::GREEN);
    long long sumBlueSquared = sumColorSquaredBlock(image, x, y, width, height, Channel::BLUE);

    double meanRed = static_cast<double> (sumRed) / count;
    double meanGreen = static_cast<double> (sumGreen) / count;
    double meanBlue = static_cast<double> (sumBlue) / count;

    double varianceRed = static_cast<double> (sumRedSquared) / count - meanRed * meanRed;
    double varianceGreen = static_cast<double> (sumGreenSquared) / count - meanGreen * meanGreen;
    double varianceBlue = static_cast<double> (sumBlueSquared) / count - meanBlue * meanBlue;

    return (varianceRed + varianceGreen + varianceBlue) / 3;
}

bool Variance::ThresholdWithinBound(double threshold) {
    return threshold >= 0 && threshold <= 16256.25;
}

std::string Variance::identify() const {
    return "Variance";
}

double Variance::getLowerBound() const {
    return 0;
}

double Variance::getUpperBound() const {
    return 16256.25;
}