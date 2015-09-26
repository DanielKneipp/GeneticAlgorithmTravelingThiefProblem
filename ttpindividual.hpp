#ifndef TTPINDIVIDUAL_HPP
#define TTPINDIVIDUAL_HPP

#include <string>
#include <sstream>

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
     * @brief operator <    Used to know if this individual is
     *                      worse than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is less than the fitness of {@ref i}.
     */
    bool operator > ( const TTPIndividual& i );
    /**
     * @brief operator <    Used to know if this individual is
     *                      worse or equal than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is less or equal than the fitness of {@ref i}.
     */
    bool operator >= ( const TTPIndividual& i );
    /**
     * @brief operator <    Used to know if this individual is
     *                      better or equal than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is greater or equal than the fitness of {@ref i}.
     */
    bool operator <= ( const TTPIndividual& i );
    /**
     * @brief operator <    Used to know if this individual is
     *                      better than the individual {@ref i}.
     *
     * @param i             Individual that will be compared to this.
     *
     * @return              \c true if the fitness of this individual
     *                      is greater than the fitness of {@ref i}.
     */
    bool operator < ( const TTPIndividual& i );
    /**
     * @brief toString      Convert the individual into a textual
     *                      representation.
     *
     * @return              String that represents the individual.
     */
    std::string toString();
};

#endif // TTPINDIVIDUAL_HPP
