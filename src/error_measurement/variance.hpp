#ifndef _VARIANCE_H_
#define _VARIANCE_H_

#include "emm.hpp"

class Variance : public EMM {
// private:
//     long long sumColorBlock(const Image& image, int x, int y, int width, int height, Channel c) const;
//     long long sumColorSquaredBlock(const Image& image, int x, int y, int width, int height, Channel c) const;
public:
    double computeBlockError(const Image& image, int x, int y, int width, int height) const override;
    bool ThresholdWithinBound(double threshold) override;
    std::string identify() const override;
    double getLowerBound() const override;
    double getUpperBound() const override;
};

#endif