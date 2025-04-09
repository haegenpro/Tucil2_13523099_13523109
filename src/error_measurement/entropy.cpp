#include "entropy.hpp"

double Entropy::computeBlockError(const Image& image, int x, int y, int width, int height) const {
    int count = width * height;
    if (count == 0) {
        return 0;
    }
    std::array<int, 256> histRed = {0};
    std::array<int, 256> histGreen = {0};
    std::array<int, 256> histBlue = {0};

    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            Pixel p = image.getPixelAt(i, j);
            histRed[p.getRed()]++;
            histGreen[p.getGreen()]++;
            histBlue[p.getBlue()]++;
        }
    }

    double entropyRed = 0;
    double entropyGreen = 0;
    double entropyBlue = 0;

    for (int i = 0; i < 256; i++) {
        if (histRed[i] > 0) {
            double probability = static_cast<double>(histRed[i]) / count;
            entropyRed -= probability * std::log2(probability);
        }
        if (histGreen[i] > 0) {
            double probability = static_cast<double>(histGreen[i]) / count;
            entropyGreen -= probability * std::log2(probability);
        }
        if (histBlue[i] > 0) {
            double probability = static_cast<double>(histBlue[i]) / count;
            entropyBlue -= probability * std::log2(probability);
        }
    }

    return (entropyRed + entropyGreen + entropyBlue) / 3;
}

bool Entropy::ThresholdWithinBound(double threshold) {
    return threshold >= 0 && threshold <= 8;
}

std::string Entropy::identify() const {
    return "Entropy";
}

double Entropy::getLowerBound() const {
    return 0;
}
double Entropy::getUpperBound() const {
    return 8;
}