#ifndef CROSSOVERMETHODS_HPP
#define CROSSOVERMETHODS_HPP

#include <vector>
#include <array>
#include <algorithm>

#include "../utils/geneticutils.hpp"

namespace CrossoverMethod
{

/**
 * @brief alternateNCutPoints       Perform a n-point crossover operation.
 *
 * @param featuresParent1           The features of parent 1.
 *
 * @param featuresParent2           The features of parent 2.
 *
 * @param cutPoints                 The list of cut points.
 *
 * @return                          The two offsprings.
 */
template< typename T_f, typename T_idx >
std::array< std::vector< T_f >, 2 > alternateNCutPoints( const std::vector< T_f >& featuresParent1,
                                                         const std::vector< T_f >& featuresParent2,
                                                         const std::vector< T_idx >& cutPoints);

/**
 * @brief orderBased            Perform an Order-based crossover operation specialized
 *                              on TSP problem to not generate invalid offsprings.
 *
 * @param featuresParent1       The features of parent 1.
 *
 * @param featuresParent2       The features of parent 2.
 *
 * @return                      The two offsprings.
 */
template< typename T_f >
std::array< std::vector< T_f >, 2 > orderBased( const std::vector< T_f >& featuresParent1,
                                                const std::vector< T_f >& featuresParent2 );

}

#include "crossovermethods.cpp"

#endif // CROSSOVERMETHODS_HPP

