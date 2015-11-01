#ifndef TTPINSTANCE_HPP
#define TTPINSTANCE_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <cmath>        // std::pow()

#include "../generic_ga/problem.hpp"

#include "ttpindividual.hpp"
#include "item.hpp"
#include "city.hpp"

class TTPInstance : public Problem< TTPIndividual >
{
private:
    /**
     * @brief penalizationMethod     Method that penalizes the individual
     *                              if he passes the knapsack capacity.
     *
     * @param totalWeight           The total weight of the items picked
     *                              by the individual.
     *
     * @return                      Value of the penalization.
     */
    double penalizationMethod( unsigned long totalWeight );
    /**
     * @brief removeWorstItemsWhileInvalid      Removes the items that has
     *                                          the worst ratios of profit by weight
     *                                          until the individual becomes valid (possible).
     *
     * @param individual                        The individual that will be changed.
     */
    void removeWorstItemsWhileInvalid( TTPIndividual& individual );


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
    /** Array of items. */
    std::vector< Item > items;
    /** Problem file name. */
    std::string probFileName;
    /** Problem file name with path. */
    std::string probFileNamePath;

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
     *                              his fitness. Cost function used is in:
     *                              A Comprehensive Benchmark Set and Heuristics.
     *                              If \ref individual is a invalid solution than
     *                              the \ref removeWorstItemsWhileInvalid() method is applied
     *                              to correct the individual removing his worst picked items 
     *                              (items with the lowest values of profit/weight) until his become
     *                              feasible.
     *
     * @param individual            \ref TTPIndividual that will be evaluated.
     */
    void evaluateIndividual( TTPIndividual& individual );
    /**
     * @brief isValidIndividual     Verify if a given individual is valid (possible).
     *
     * @param individual            The individual.
     *
     * @return                      \c true if the individual is valid, \c false otherwise.
     */
    bool isValidIndividual( TTPIndividual& individual );
};

#endif // TTPINSTANCE_HPP
