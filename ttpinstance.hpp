#ifndef TTPINSTANCE_H
#define TTPINSTANCE_H

#include <string>
#include <fstream>
#include <memory>

#include "item.hpp"
#include "city.hpp"


class TTPInstance
{
public:
    /** Specify if the problem is already loaded from a file. */
    bool isLoaded;
    /** Number of cities. */
    unsigned long numCities;
    /** Number of items. */
    unsigned long numItems;
    /** Knapsack capacity (W). */
    unsigned long knapCapacity;
    /** Maximal speed (Vmax). */
    float speedMax;
    /** Minimal speed (Vmin). */
    float speedMin;
    /** Renting ratio (R). */
    float rentingRatio;
    /** Array of cities. */
    std::unique_ptr< City[] > cities;
    /** Array of items */
    std::unique_ptr< Item[] > items;

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
    TTPInstance( std::string fileName = "" );

    /**
     * @brief   readProblem     Load a TTP from file.
     *
     * @param   fileName        File that specify the TTP.
     */
    void readProblem( std::string fileName );

};

#endif // TTPINSTANCE_H
