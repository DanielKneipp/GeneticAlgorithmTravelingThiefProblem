#ifndef TTPINDIVIDUALFEATURES_HPP
#define TTPINDIVIDUALFEATURES_HPP

#include <vector>

#include "features.hpp"

class TTPIndividualFeatures : public Features
{
public:
    /** Tour (with the last city which is the same as the first). */
    std::vector< unsigned long > tour;
    /** Picking plan (array of 0s and 1s). */
    std::vector< unsigned char > pickingPlan;

    /**
     * @brief TTPIndividualFeatures     Constructor.
     */
    TTPIndividualFeatures();
};

#endif // TTPINDIVIDUALFEATURES_HPP
