#ifndef _MAD_H_
#define _MAD_H_

#include "emm.hpp"
#include <cmath>

class MAD : public EMM {
private:
    double meanColorBlock(const Image& image, int x, int y, int width, int height, Channel c) const;
public:
    double computeBlockError(const Image& image, int x, int y, int width, int height) const override;
    bool ThresholdWithinBound(double threshold) override;
};

#endif