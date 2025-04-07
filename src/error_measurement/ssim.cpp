#include "ssim.hpp"

static constexpr double k1 = 0.01;
static constexpr double k2 = 0.03;
static constexpr double L  = 255.0;

static double computeChannelSSIM(double sumRef, double sumTest, double sumRef2, double sumTest2, double sumRefTest, int count)
{
    double meanRef = sumRef / count;
    double meanTest = sumTest / count;
    double varRef  = (sumRef2 / count) - (meanRef * meanRef);
    double varTest = (sumTest2 / count) - (meanTest * meanTest);
    double cov     = (sumRefTest / count) - (meanRef * meanTest);
    double c1 = (k1 * L) * (k1 * L);
    double c2 = (k2 * L) * (k2 * L);
    double numerator   = (2.0 * meanRef * meanTest + c1) * (2.0 * cov + c2);
    double denominator = (meanRef * meanRef + meanTest * meanTest + c1) * (varRef + varTest + c2);
    if (denominator < 1e-12)
        return 1.0; 
    return numerator / denominator;
}

double SSIM::computeBlockError(const Image& refImg, const Image& testImg,
                               int x, int y, int width, int height) const
{
    int count = width * height;
    
    double sumRRef = 0.0, sumRTest = 0.0, sumRRef2 = 0.0, sumRTest2 = 0.0, sumRRefTest = 0.0;
    double sumGRef = 0.0, sumGTest = 0.0, sumGRef2 = 0.0, sumGTest2 = 0.0, sumGRefTest = 0.0;
    double sumBRef = 0.0, sumBTest = 0.0, sumBRef2 = 0.0, sumBTest2 = 0.0, sumBRefTest = 0.0;

    for (int j = y; j < y + height; j++) {
        for (int i = x; i < x + width; i++) {
            Pixel pref = refImg.getPixelAt(i, j);
            Pixel ptest = testImg.getPixelAt(i, j);

            double rRef = static_cast<double>(pref.getRed());
            double rTest = static_cast<double>(ptest.getRed());
            double gRef = static_cast<double>(pref.getGreen());
            double gTest = static_cast<double>(ptest.getGreen());
            double bRef = static_cast<double>(pref.getBlue());
            double bTest = static_cast<double>(ptest.getBlue());
            sumRRef      += rRef;
            sumRTest     += rTest;
            sumRRef2     += rRef * rRef;
            sumRTest2    += rTest * rTest;
            sumRRefTest  += rRef * rTest;
            sumGRef      += gRef;
            sumGTest     += gTest;
            sumGRef2     += gRef * gRef;
            sumGTest2    += gTest * gTest;
            sumGRefTest  += gRef * gTest;
            sumBRef      += bRef;
            sumBTest     += bTest;
            sumBRef2     += bRef * bRef;
            sumBTest2    += bTest * bTest;
            sumBRefTest  += bRef * bTest;
        }
    }
    double ssimR = computeChannelSSIM(sumRRef, sumRTest, sumRRef2, sumRTest2, sumRRefTest, count);
    double ssimG = computeChannelSSIM(sumGRef, sumGTest, sumGRef2, sumGTest2, sumGRefTest, count);
    double ssimB = computeChannelSSIM(sumBRef, sumBTest, sumBRef2, sumBTest2, sumBRefTest, count);

    double ssim = (ssimR + ssimG + ssimB) / 3.0;
    return ssim;
}

bool SSIM::ThresholdWithinBound(double threshold)
{
    return (threshold >= 0.0 && threshold <= 1.0);
}
