#ifndef TTPINDIVIDUAL_HPP
#define TTPINDIVIDUAL_HPP

#include <string>

#include "individual.hpp"
#include "ttpindividualfeatures.hpp"

class TTPIndividual : public Individual< TTPIndividualFeatures >
{
public:
    /**
     * @brief TTPIndividual     Constructor.
     */
    TTPIndividual();
    /**
     * @brief ~TTPIndividual    Destructor.
     */
    ~TTPIndividual();
    /**
     * @brief toString      Convert the individual into a textual
     *                      representation.
     *
     * @return              String that represents the individual.
     */
    std::string toString() const ;
};

#endif // TTPINDIVIDUAL_HPP
