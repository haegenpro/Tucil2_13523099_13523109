#ifndef _EMM_H_
#define _EMM_H_

#include <string>
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
    virtual long long sumColorBlock(const Image& image, int x, int y, int width, int height, Channel c) const;
    virtual long long sumColorSquaredBlock(const Image& image, int x, int y, int width, int height, Channel c) const;
    virtual double meanColorBlock(const Image& image, int x, int y, int width, int height, Channel c) const;
    virtual std::string identify() const = 0;
    virtual double getLowerBound() const = 0;
    virtual double getUpperBound() const = 0;
    virtual ~EMM() = default;
};

#endif