#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>
#include <memory>
#include "image.hpp"

class Animation {
private:
    struct Impl;
    std::unique_ptr<Impl> impl;

public:
    Animation(const std::string& path, int width, int height, int delay = 70);
    ~Animation();

    void addFrame(const Image& image);
    void close();
};

#endif
