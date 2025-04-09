#ifndef SSIM_HPP
#define SSIM_HPP

#include "emm.hpp"
#include "../image/image.hpp"  // Adjust the path as needed
#include <cmath>

class SSIM : public EMM {
private:
    static double computeChannelSSIM(double sumRef, double sumTest, double sumRef2, double sumTest2, double sumRefTest, int count);
    // double meanColorBlock(const Image& image, int x, int y, int width, int height, Channel c) const;
public:
    double computeBlockError(const Image& refImg, int x, int y, int width, int height) const override;
    bool ThresholdWithinBound(double threshold) override;
    bool isWithinThreshold(double error, double threshold) const override;
    std::string identify() const override;
    double getLowerBound() const override;
    double getUpperBound() const override;
};

#endif
