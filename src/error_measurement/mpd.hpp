#ifndef _MPD_H_
#define _MPD_H_

#include "emm.hpp"
#include <cmath>

class MPD : public EMM {
public:
    double computeBlockError(const Image& image, int x, int y, int width, int height) const override;
    bool thresholdWithinBound(double threshold);
};

#endif