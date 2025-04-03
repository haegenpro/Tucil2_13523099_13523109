#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <filesystem>
#include <cstring>
#include <iostream>
#include "../pixel/pixel.h"

namespace fs = std::filesystem;

class Image {
private:
    fs::path path;
    std::string extension;
    int width;
    int height;
    int channels;
    unsigned char* data;
    std::uintmax_t fileSize;

public:
    Image(const fs::path& path);
    Image(const Image&);
    ~Image();
    bool load(const fs::path& filePath);
    bool save(const fs::path& outPath) const;
    fs::path getPath() const;
    std::string getExtension() const;
    int getWidth() const;
    int getHeight() const;
    int getChannels() const;
    unsigned char* getData() const;
    std::uintmax_t getFileSize() const; 
    Pixel getPixelAt(int x, int y) const;
    void setPixelAt(int x, int y, Pixel p);
};

#endif