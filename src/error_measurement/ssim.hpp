#ifndef SSIM_HPP
#define SSIM_HPP

#include "emm.hpp"
#include "../image/image.hpp"  // Adjust the path as needed
#include <cmath>

class SSIM : public EMM {
public:
    double computeBlockError(const Image& refImg, const Image& testImg, int x, int y, int width, int height) const;
    bool ThresholdWithinBound(double threshold) override;
};

#endif
