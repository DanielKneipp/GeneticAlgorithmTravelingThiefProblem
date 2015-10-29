#ifndef TTPGA_HPP
#define TTPGA_HPP

#include "../defines.hpp"

#include <vector>
#include <algorithm>
#include <functional>
#include <exception>
#include <string>
#include <chrono>
#include <numeric>
#include <cstdlib>  // std::system()
#include <cstdio>   // std::remove()

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
    /** Number of individuals (population size). */
    unsigned NUM_INDIVIDUALS;
    /** Maximum number of generations without any improvement. */
    unsigned MAX_GENS_WITHOUT_IMPROV;
    /** Maximum execution time. */
    std::chrono::milliseconds MAX_EXEC_TIME;
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
    unsigned    NUM_CUT_POINTS ;
    /** Probability of a item be picked or removed from the knapsack.
      * Used in mutation step (KP component). */
    float       ALPHA_PROBABILITY;
    /** Name of the configuration (will appear as the data label in the plot). */
    std::string CONFIG_NAME;

    /**
     * @brief TTPGAConfig   Constructor.
     */
    TTPGAConfig();
    /**
     * @brief toString      Convert \ref TTPGAConfig to his string representation.
     */
    std::string toString() const;
    /**
     * @brief readTTPGAConfigFromFile   Read the configuration of TTPGA from a file
     *
     * @return                          The configuration structure.
     */
    static TTPGAConfig readTTPGAConfigFromFile( std::string fileNamePath );
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
     * @param lkOutFileName         File that will store the output generated
     *                              by the Lin-Kernighan program.
     *
     * @param delFile               Set to \c true to delete the file \ref lkOutFileName
     *                              after the execution of this method.
     *
     * @return                      A solution for the TSP component (tour).
     */
    std::vector< unsigned long > getLinkernTour( std::string lkOutFileName, bool delFile = false );
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
    /** Number of processed generations */
    std::size_t numProcGens;
    /** Configuration of the GA. */
    TTPGAConfig gaConfig;

    /**
     * @brief TTPGA     Constructor.
     */
    TTPGA();
    /**
     * @brief run       Execute the evolutionary solver method.
     */
    virtual void run();
};

#endif // TTPGA_HPP
