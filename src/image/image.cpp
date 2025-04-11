#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "../include/stb_image_write.h"
#include "image.hpp"

Image::Image(const fs::path& filePath) : data(nullptr), width(0), height(0), channels(0), fileSize(0) {
    load(filePath);
}

Image::Image(const Image& other) : width(other.width), height(other.height), channels(other.channels), path(other.path), extension(other.extension), fileSize(other.fileSize) {
    int dataSize = width * height * channels;
    data = static_cast<unsigned char*>(malloc(dataSize));
    if (data && other.data) {
        std::memcpy(data, other.data, dataSize);
    }
}

Image::~Image() {
    if (data) {
        stbi_image_free(data);
        data = nullptr;
    }
}

bool Image::load(const fs::path& filePath) {
    if (data) {
        stbi_image_free(data);
        data = nullptr;
    }

    path = filePath;
    extension = path.extension().string();

    data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load image: " << path << std::endl;
        return false;
    }

    try {
        fileSize = fs::file_size(path);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error getting file size: " << e.what() << std::endl;
        fileSize = 0;
    }

    return true;
}

bool Image::save(const fs::path& outPath) const {
    if (!data) {
        std::cerr << "Error: No image data to save.\n";
        return false;
    }

    std::string ext = outPath.extension().string();
    int stride = width * channels;
    bool success = false;

    if (ext == ".png") {
        stbi_write_png_compression_level = 9;
        stbi_write_force_png_filter = 4;
        success = stbi_write_png(outPath.string().c_str(), width, height, channels, data, stride);
    } else if (ext == ".jpg" || ext == ".jpeg") {
        success = stbi_write_jpg(outPath.string().c_str(), width, height, channels, data, 75);
    } else {
        std::cerr << "Unsupported file format for saving: " << ext << std::endl;
        return false;
    }

    if (!success) {
        std::cerr << "Failed to save image to: " << outPath << std::endl;
    }

    return success;
}

fs::path Image::getPath() const {
    return path;
}

std::string Image::getExtension() const {
    return extension;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

int Image::getChannels() const {
    return channels;
}

unsigned char* Image::getData() const {
    return data;
}

std::uintmax_t Image::getFileSize() const {
    return fileSize;
}

Pixel Image::getPixelAt(int x, int y) const {
    if (!data || x < 0 || x >= width || y < 0 || y >= height) {
        return Pixel();
    }

    int index = (y * width + x) * channels;
    unsigned char r = data[index];
    unsigned char g = (channels >= 2) ? data[index + 1] : r;
    unsigned char b = (channels >= 3) ? data[index + 2] : r;
    unsigned char a = (channels == 4) ? data[index + 3] : 255;

    return Pixel(r, g, b, a);
}

void Image::setPixelAt(int x, int y, Pixel p) {
    if (!data || x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    int index = (y * width + x) * channels;
    data[index] = p.getRed();
    if (channels >= 2) {
        data[index + 1] = p.getGreen();
    }
    if (channels >= 3) {
        data[index + 2] = p.getBlue();
    }
    if (channels == 4) {
        data[index + 3] = p.getAlpha();
    }
}

void Image::countBytes(void* context, void* data, int size) {
    size_t* byteCount = static_cast<size_t*>(context);
    *byteCount += static_cast<size_t>(size);
}

void Image::setFileSize(std::uintmax_t size) {
    fileSize = size;
}

uintmax_t Image::estimateNewFileSize() const {
    uintmax_t byteCount = 0;

    if (extension == ".png") {
        int stride = width * channels;
        stbi_write_png_compression_level = 9;
        stbi_write_force_png_filter = 4;
        stbi_write_png_to_func(countBytes, &byteCount, width, height, channels, data, stride);
    } else if (extension == ".jpeg" || extension == ".jpg") {
        stbi_write_jpg_to_func(countBytes, &byteCount, width, height, channels, data, 75);
    } else {
        std::cerr << "Unsupported file format for saving: " << extension << std::endl;
        return 0;
    }
    
    return byteCount;
}