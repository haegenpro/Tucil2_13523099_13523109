#include "emm.hpp"

bool EMM::isWithinThreshold(double error, double threshold) const {
    return error <= threshold;
}

