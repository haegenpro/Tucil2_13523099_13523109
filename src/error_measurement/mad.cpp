#include "mad.hpp"

// double MAD::meanColorBlock(const Image& image, int x, int y, int width, int height, Channel c) const {
//     long long sum = 0;
//     int count = width * height;

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
//     return static_cast<double> (sum) / count;
// }

double MAD::computeBlockError(const Image& image, int x, int y, int width, int height) const {
    int count = width * height;

    double meanRed = meanColorBlock(image, x, y, width, height, Channel::RED);
    double meanGreen = meanColorBlock(image, x, y, width, height, Channel::GREEN);
    double meanBlue = meanColorBlock(image, x, y, width, height, Channel::BLUE);

    double absDifSumRed = 0;
    double absDifSumGreen = 0;
    double absDifSumBlue = 0;

    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            Pixel p = image.getPixelAt(i, j);
            absDifSumRed += std::abs(p.getRed() - meanRed);
            absDifSumGreen += std::abs(p.getGreen() - meanGreen);
            absDifSumBlue += std::abs(p.getBlue() - meanBlue);
        }
    }

    double madRed = absDifSumRed / count;
    double madGreen = absDifSumGreen / count;
    double madBlue = absDifSumBlue / count;

    return (madRed + madGreen + madBlue) / 3;
}

bool MAD::ThresholdWithinBound(double threshold) {
    return threshold >= 0 && threshold <= 127.5;
}