#ifndef TTPGA_HPP
#define TTPGA_HPP

#include <vector>
#include <algorithm>
#include <exception>
#include <string>
#ifdef _MSC_VER
    #include <numeric> // std::iota
#endif // _MSC_VER

#include "../generic_ga/evolutionaryoptimizer.hpp"
#include "../generic_ga/individual.hpp"
#include "../generic_ga/selectionmethods.hpp"

#include "../utils/individualrecorder.hpp"

#include "ttpinstance.hpp"
#include "ttpmutationmethods.hpp"
#include "ttpcrossovermethods.hpp"

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
    /** Specify the output direcotory of the execution data. */
    std::string outputDirectory;

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
