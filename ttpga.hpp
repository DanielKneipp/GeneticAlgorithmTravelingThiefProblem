#ifndef TTPGA_HPP
#define TTPGA_HPP

#include <vector>
#include <algorithm>
#include <exception>
#include <string>

#include "evolutionaryoptimizer.hpp"
#include "individual.hpp"
#include "ttpinstance.hpp"
#include "ttpmutationmethods.hpp"
#include "selectionmethods.hpp"
#include "individualrecorder.hpp"

class TTPGA : public EvolutionaryOptimizer< TTPIndividual, TTPInstance >
{
protected:
    /**
     * @brief generatePopulation    Generate the population. Commonly used to
     *                              create the initial population.
     *
     * @param numIndividuals        Number of individuals that will be generated.
     *
     * @return                      The generated individuals.
     */
    virtual std::vector< TTPIndividual > generatePopulation( unsigned numIndividuals );


public:
    /**
     * @brief TTPGA     Constructor.
     */
    TTPGA();
    /**
     * @brief run       Execute the evolutionary solver method.
     */
    virtual void run( unsigned numIndividuals,
                      unsigned numGenerations = 0 );
};

#endif // TTPGA_HPP
