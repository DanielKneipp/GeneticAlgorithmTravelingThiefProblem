#include "ttpindividualfeatures.hpp"

TTPIndividualFeatures::TTPIndividualFeatures() {}

std::string TTPIndividualFeatures::toString() const
{
    std::string outPut;

    outPut += "{\n";

    outPut += "\"tour\" : [ ";
    if( this->tour.size() > 0 )
    {
        for( auto&& city : this->tour )
        {
            outPut += std::to_string( city ) += ", ";
        }
        outPut.pop_back();
    }
    outPut += "],\n";

    outPut += "\"pickingPlan\" : [ ";
    if( this->tour.size() > 0 )
    {
        for( auto&& item : this->pickingPlan )
        {
            outPut += std::to_string( item ) += ", ";
        }
        outPut.pop_back();
    }
    outPut += "]\n";

    outPut += "}";

    return outPut;
}
