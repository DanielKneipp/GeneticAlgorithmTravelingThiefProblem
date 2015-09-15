#ifndef TTPINDIVIDUALFEATURES_HPP
#define TTPINDIVIDUALFEATURES_HPP

#include <vector>

#include "features.hpp"

class TTPIndividualFeatures : public Features
{
public:
    std::vector< unsigned long > tour;

    std::vector< unsigned char > pickingPlan;


    TTPIndividualFeatures();
};

#endif // TTPINDIVIDUALFEATURES_HPP
