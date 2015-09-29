#ifndef TTPINDIVIDUALFEATURES_HPP
#define TTPINDIVIDUALFEATURES_HPP

#include <vector>
#include <string>

#include "features.hpp"

class TTPIndividualFeatures : public Features
{
public:
    /** Tour (with the last city which is the same as the first). */
    std::vector< unsigned long > tour;
    /** Picking plan (array of 0s and 1s). */
    std::vector< unsigned short > pickingPlan;

    /**
     * @brief TTPIndividualFeatures     Constructor.
     */
    TTPIndividualFeatures();
    /**
     * @brief toString  Used to get a \c string representation of the features.
     *
     * @return          a \c string representation of the features.
     */
    std::string toString() const ;
};

#endif // TTPINDIVIDUALFEATURES_HPP
