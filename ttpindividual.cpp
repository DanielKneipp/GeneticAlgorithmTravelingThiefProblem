#include "ttpindividual.hpp"

TTPIndividual::TTPIndividual() {}

bool TTPIndividual::operator < ( const TTPIndividual& i )
{
    return this->fitness > i.fitness;
}

bool TTPIndividual::operator <= ( const TTPIndividual& i )
{
    return this->fitness >= i.fitness;
}

bool TTPIndividual::operator > ( const TTPIndividual& i )
{
    return this->fitness < i.fitness;
}

bool TTPIndividual::operator >= ( const TTPIndividual& i )
{
    return this->fitness <= i.fitness;
}

std::string TTPIndividual::toString()
{
    std::stringstream outPut;

    outPut << "{\n";

    outPut << "\"tour\" : [ ";
    for( auto&& city : this->features.tour )
    {
        outPut << std::to_string( city ) << ", ";
    }
    outPut << "],\n";

    outPut << "\"pickingPlan\" : [ ";
    for( auto&& item : this->features.pickingPlan )
    {
        outPut << std::to_string( item ) << ", ";
    }
    outPut << "],\n";

    outPut << "\"fitness\" : " << std::to_string( this->fitness ) << "\n";

    outPut << "}";

    return outPut.str();
}
