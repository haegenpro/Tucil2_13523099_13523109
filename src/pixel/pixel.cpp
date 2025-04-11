#include "pixel.hpp"

Pixel::Pixel() : r(0), g(0), b(0), a(255) {}
    
Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) : r(red), g(green), b(blue), a(alpha) {}

Pixel::~Pixel() {}

bool Pixel::operator==(const Pixel& other) const {
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

Pixel& Pixel::operator=(const Pixel& other) {
    if (this != &other) {
        this->r = other.r;
        this->g = other.g;
        this->b = other.b;
        this->a = other.a;
    }
    return *this;
}

unsigned char Pixel::getRed() const {
    return this->r;
}

unsigned char Pixel::getGreen() const {
    return this->g;
}

unsigned char Pixel::getBlue() const {
    return this->b;
}

unsigned char Pixel::getAlpha() const {
    return this->a;
}

void Pixel::setRed(unsigned char val) {
    this->r = val;
}

void Pixel::setGreen(unsigned char val) {
    this->g = val;
}

void Pixel::setBlue(unsigned char val) {
    this->b = val;
}

void Pixel::setAlpha(unsigned char val) {
    this->a = val;
}