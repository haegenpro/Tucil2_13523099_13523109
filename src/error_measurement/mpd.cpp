#include "mpd.hpp"

double MPD::computeBlockError(const Image& image, int x, int y, int width, int height) const {
    Pixel p = image.getPixelAt(x, y);

    int minRed = p.getRed();
    int minGreen = p.getGreen();
    int minBlue = p.getBlue();

    int maxRed = p.getRed();
    int maxGreen = p.getGreen();
    int maxBlue = p.getBlue();

    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            p = image.getPixelAt(i, j);
            minRed = std::min(minRed, static_cast<int>(p.getRed()));
            minGreen = std::min(minGreen, static_cast<int>(p.getGreen()));
            minBlue = std::min(minBlue, static_cast<int>(p.getBlue()));
            maxRed = std::max(maxRed, static_cast<int>(p.getRed()));
            maxGreen = std::max(maxGreen, static_cast<int>(p.getGreen()));
            maxBlue = std::max(maxBlue, static_cast<int>(p.getBlue()));
        }
    }

    int redDif = maxRed - minRed;
    int greenDif = maxGreen - minGreen;
    int blueDif = maxBlue - minBlue;

    return static_cast<double>(redDif + greenDif + blueDif) / 3;
}

bool MPD::ThresholdWithinBound(double threshold) {
    return threshold >= 0 && threshold <= 255;
}

std::string MPD::identify() const {
    return "MPD";
}

double MPD::getLowerBound() const {
    return 0;
}

double MPD::getUpperBound() const {
    return 255;
}