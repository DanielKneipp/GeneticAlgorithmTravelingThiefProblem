#ifndef TTPINSTANCE_H
#define TTPINSTANCE_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

#include "../generic_ga/problem.hpp"
#include "ttpindividual.hpp"
#include "item.hpp"
#include "city.hpp"

class TTPInstance : public Problem< TTPIndividual >
{
private:
    /**
     * @brief penalizationMethod     Method that penalizies the individual
     *                              if he passes tha knapsack capacity.
     *
     * @param totalWeight           The total weight of the items picked
     *                              by the individual.
     *
     * @return                      Value of the penalization.
     */
    double penalizationMethod( unsigned long totalWeight );


public:    
    /** Number of cities. */
    unsigned long numCities;
    /** Number of items. */
    unsigned long numItems;
    /** Number of items per city */
    unsigned long numItemsPerCity;
    /** Knapsack capacity (W). */
    unsigned long knapCapacity;
    /** Maximal speed (Vmax). */
    double speedMax;
    /** Minimal speed (Vmin). */
    double speedMin;
    /** Renting rate (R). */
    double rentingRate;
    /** Array of cities. */
    std::vector< City > cities;
    /** Array of items */
    std::vector< Item > items;

    /**
     * @brief TTPInstance   Constructor.
     *
     * @param fileName      File that will initialize the Object
     *                      calling the { @link readProblem( std::string fileName ) }
     *                      passing \ref fileName as parameter to him. If not path is set
     *                      then a empty string is set (\c "") by default, in that case
     *                      no TTP is loaded, all variables are set to \c 0 and the arrays
     *                      are not allocated.
     */
    TTPInstance( const std::string& fileName = "" );
    /**
     * @brief   readProblem     Load a Problem from file.
     *
     * @param   fileName        File that specify the Problem.
     */
    void readProblem( const std::string& fileName );
    /**
     * @brief evaluateIndividual    Evaluate the individual and set
     *                              his fitness. Cost funtion used is in:
     *                              A Comprehensive Benchmark Set and Heuristics.
     *
     * @param individual            \ref TTPIndividual that will be evaluated.
     */
    void evaluateIndividual( TTPIndividual& individual );
};

#endif // TTPINSTANCE_H
