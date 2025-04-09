#ifndef _VARIANCE_H_
#define _VARIANCE_H_

#include "emm.hpp"

class Variance : public EMM {

public:
    double computeBlockError(const Image& image, int x, int y, int width, int height) const override;
    bool ThresholdWithinBound(double threshold) override;
};

#endif