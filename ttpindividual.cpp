#include "ttpindividual.hpp"

TTPIndividual::TTPIndividual() {}

bool TTPIndividual::operator < ( const Individual< TTPIndividualFeatures >& i )
{
    return this->fitness > i.fitness;
}

bool TTPIndividual::operator <= ( const Individual< TTPIndividualFeatures >& i )
{
    return this->fitness >= i.fitness;
}

bool TTPIndividual::operator > ( const Individual< TTPIndividualFeatures >& i )
{
    return this->fitness < i.fitness;
}

bool TTPIndividual::operator >= ( const Individual< TTPIndividualFeatures >& i )
{
    return this->fitness <= i.fitness;
}

std::string TTPIndividual::toString()
{
    std::string outPut;

    outPut += "{\n";

    outPut += "\"tour\" : [ ";
    if( this->features.tour.size() > 0 )
    {
        for( auto&& city : this->features.tour )
        {
            outPut += std::to_string( city ) += ", ";
        }
        outPut.pop_back();
    }
    outPut += "],\n";

    outPut += "\"pickingPlan\" : [ ";
    if( this->features.tour.size() > 0 )
    {
        for( auto&& item : this->features.pickingPlan )
        {
            outPut += std::to_string( item ) += ", ";
        }
        outPut.pop_back();
    }
    outPut += "],\n";

    outPut += "\"fitness\" : " += std::to_string( this->fitness ) += "\n";

    outPut += "}";

    return outPut;
}
