#ifndef TTPCROSSOVERMETHODS_HPP
#define TTPCROSSOVERMETHODS_HPP

#include <vector>
#include <array>
#include <algorithm>

#include "../generic_ga/crossovermethods.hpp"

#include"../utils/geneticutils.hpp"

#include "ttpindividual.hpp"

namespace TTPCrossoverMethod
{

/**
 * @brief orderBased_alternate      Perform a n-point crossover operation for KP component
 *                                  and an Order-based crossover operation for TSP component.
 *
 * @param population                The arra of {@ref TTPIndividual}.
 *
 * @param numCutPoints              Number of cut points required. They will be generated
 *                                  randomly.
 *
 * @return                          The offsprings.
 */
std::vector< TTPIndividual > orderBased_alternate( const std::vector< TTPIndividual >& population,
                                                   const unsigned numCutPoints = 1 );

}

#endif // TTPCROSSOVERMETHODS_HPP

