#include "animation.hpp"
#include "../include/gif.h"
#include <iostream>

struct Animation::Impl {
    GifWriter writer;
    bool init;
    int width, height, delay;

    Impl(const std::string& path, int w, int h, int d)
        : init(false), width(w), height(h), delay(d)
    {
        init = GifBegin(&writer, path.c_str(), width, height, delay);
    }

    ~Impl() {
        if (init) GifEnd(&writer);
    }

    void addFrame(const Image& image) {
        if (!init) return;

        int imgChannels = image.getChannels();
        unsigned char* imgData = image.getData();

        if (imgChannels == 4) {
            GifWriteFrame(&writer, imgData, width, height, delay);
            return;
        }

        unsigned char* rgba = new unsigned char[width * height * 4];
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int idx_src = (x + y * width) * imgChannels;
                int idx_dest = (x + y * width) * 4;

                unsigned char r = 0, g = 0, b = 0, a = 255;
                if (imgChannels == 1) {
                    r = g = b = imgData[idx_src];
                } else if (imgChannels == 3) {
                    r = imgData[idx_src];
                    g = imgData[idx_src + 1];
                    b = imgData[idx_src + 2];
                } else {
                    std::cerr << "Unsupported image channel count: " << imgChannels << std::endl;
                    delete[] rgba;
                    return;
                }

                rgba[idx_dest + 0] = r;
                rgba[idx_dest + 1] = g;
                rgba[idx_dest + 2] = b;
                rgba[idx_dest + 3] = a;
            }
        }

        GifWriteFrame(&writer, rgba, width, height, delay);
        delete[] rgba;
    }

    void close() {
        if (init) {
            GifEnd(&writer);
            init = false;
        }
    }
};

Animation::Animation(const std::string& path, int width, int height, int delay)
    : impl(std::make_unique<Impl>(path, width, height, delay))
{}

Animation::~Animation() = default;

void Animation::addFrame(const Image& image) {
    impl->addFrame(image);
}

void Animation::close() {
    impl->close();
}
