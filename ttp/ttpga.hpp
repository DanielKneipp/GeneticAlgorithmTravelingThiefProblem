#ifndef TTPGA_HPP
#define TTPGA_HPP

#include "../defines.hpp"

#include <vector>
#include <algorithm>
#include <functional>
#include <exception>
#include <string>
#include <cstdlib>  // std::system()
#include <cstdio>   // std::remove()
#ifdef _MSC_VER
#include <numeric>  // std::iota()
#endif // _MSC_VER

#include "../generic_ga/evolutionaryoptimizer.hpp"
#include "../generic_ga/individual.hpp"
#include "../generic_ga/selectionmethods.hpp"
#if defined( __GA_PLOT_ ) || defined( __GA_LOG_ )
#include "../utils/individualrecorder.hpp"
#endif // __GA_PLOT_ || __GA_LOG_

#include "ttpinstance.hpp"
#include "ttpmutationmethods.hpp"
#include "ttpcrossovermethods.hpp"

struct TTPGAConfig
{
    /** The size of the tournament in the selection step. */
    std::size_t TOURNAMET_SIZE;
    /** The size of the tournament in the crossover step. */
    std::size_t TOURNAMET_SIZE_CROSSOVER;
    /** The number of elite solutions in the selection step. */
    std::size_t SELECTION_NUM_ELITES;
    /** The number of elite solutions in the crossover step. */
    std::size_t SELECTION_NUM_ELITES_CROSSOVER;
    /** The number of elites in the mutation step. */
    std::size_t MUTATION_NUM_ELITES;
    /** Number of cut points used in the crossover step (KP component).  */
    unsigned    NUM_CUT_POINTS;
    /** Probability of a a item be picked or removed from the knapsack. 
      * Used in mutation step (KP component). */
    float       ALPHA_PROBABILITY;
    /** Name of the configuration (will appear as the data label in the plot). */
    std::string CONFIG_NAME;

    /**
     * @brief toString      Convert \ref TTPGAConfig to his string representation.
     */
    std::string toString() const
    {
        return std::string( "TOURNAMET_SIZE: " ) + std::to_string( this->TOURNAMET_SIZE ) + "\n"
             + std::string( "TOURNAMET_SIZE_CROSSOVER: " ) + std::to_string( this->TOURNAMET_SIZE_CROSSOVER ) + "\n"
             + std::string( "SELECTION_NUM_ELITES: " ) + std::to_string( this->SELECTION_NUM_ELITES ) + "\n"
             + std::string( "SELECTION_NUM_ELITES_CROSSOVER: " ) + std::to_string( this->SELECTION_NUM_ELITES_CROSSOVER ) + "\n"
             + std::string( "MUTATION_NUM_ELITES: " ) + std::to_string( this->MUTATION_NUM_ELITES ) + "\n"
             + std::string( "NUM_CUT_POINTS: " ) + std::to_string( this->NUM_CUT_POINTS ) + "\n"
             + std::string( "ALPHA_PROBABILITY: " ) + std::to_string( this->ALPHA_PROBABILITY ) + "\n"
             + std::string( "CONFIG_NAME: " ) + this->CONFIG_NAME;
    }
};

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
    /**
     * @brief getLinkernTour        Generate a solution for TSP component
     *                              given by the Lin-Kernighan algorithm.
     *
     * @return                      A solution for the TSP component (tour).
     */
    std::vector< unsigned long > getLinkernTour( std::string lkOutFileName );
    /**
     * @brief genRandTSPComponent   Generate a random solution (feasible) for 
     *                              TSP component.
     *
     * @return                      A solution for the TSP component (tour).
     */
    std::vector< unsigned long > genRandTSPComponent();


public:
    /** Specify the output directory of the execution data. */
    std::string outputDirectory;
    /** Configuration of the GA. */
    TTPGAConfig gaConfig;

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
