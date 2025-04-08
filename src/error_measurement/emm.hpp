#ifndef _EMM_H_
#define _EMM_H_

#include "../image/image.hpp"

class EMM {
public:
    enum class Channel {
        RED,
        GREEN,
        BLUE
    };

    virtual double computeBlockError(const Image& image, int x, int y, int width, int height) const = 0;
    virtual bool ThresholdWithinBound(double threshold) = 0;
    virtual bool isWithinThreshold(double error, double threshold) const;
    virtual ~EMM() = default;
};

#endif