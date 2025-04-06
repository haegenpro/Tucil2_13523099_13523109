#include "emm.hpp"

bool EMM::isWithinThreshold(double error, double threshold) {
    return error <= threshold;
}

