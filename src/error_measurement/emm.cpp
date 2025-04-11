#include "emm.hpp"

bool EMM::isWithinThreshold(double error, double threshold) const {
    return error <= threshold;
}

long long EMM::sumColorBlock(const Image& image, int x, int y, int width, int height, Channel c) const {
    long long sum = 0;

    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            Pixel p = image.getPixelAt(i, j);
            switch(c) {
                case Channel::RED:
                    sum += p.getRed();
                    break;
                case Channel::GREEN:
                    sum += p.getGreen();
                    break;
                case Channel::BLUE:
                    sum += p.getBlue();
                    break;
            }
        }
    }
    return sum;
}

long long EMM::sumColorSquaredBlock(const Image& image, int x, int y, int width, int height, Channel c) const {
    long long sum = 0;

    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            Pixel p = image.getPixelAt(i, j);
            switch(c) {
                case Channel::RED:
                    sum += p.getRed() * p.getRed();
                    break;
                case Channel::GREEN:
                    sum += p.getGreen() * p.getGreen();
                    break;
                case Channel::BLUE:
                    sum += p.getBlue() * p.getBlue();
                    break;
            }
        }
    }
    return sum;
}

double EMM::meanColorBlock(const Image& image, int x, int y, int width, int height, Channel c) const {
    long long sum = 0;
    const int count = width * height;
    
    for (int j = y; j < y + height; j++) {
        for (int i = x; i < x + width; i++) {
            Pixel p = image.getPixelAt(i, j);
            switch(c) {
                case Channel::RED:
                    sum += p.getRed();
                    break;
                case Channel::GREEN:
                    sum += p.getGreen();
                    break;
                case Channel::BLUE:
                    sum += p.getBlue();
                    break;
            }
        }
    }
    return static_cast<double>(sum) / count;
}