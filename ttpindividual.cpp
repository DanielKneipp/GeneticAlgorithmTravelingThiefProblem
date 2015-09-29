#include "ttpindividual.hpp"

TTPIndividual::TTPIndividual() {}

TTPIndividual::~TTPIndividual() {}

std::string TTPIndividual::toString() const
{
    std::string outPut;

    outPut += "{\n";

    outPut += "\"features\" : " + this->features.toString() + ",\n";

    outPut += "\"fitness\" : " + std::to_string( this->fitness ) + "\n";

    outPut += "}";

    return outPut;
}
