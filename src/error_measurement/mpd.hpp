#ifndef _MPD_H_
#define _MPD_H_

#include "emm.hpp"
#include <cmath>

class MPD : public EMM {
public:
    double computeBlockError(const Image& image, int x, int y, int width, int height) const override;
    bool ThresholdWithinBound(double threshold) override;
    std::string identify() const override;
    double getLowerBound() const override;
    double getUpperBound() const override;
};

#endif