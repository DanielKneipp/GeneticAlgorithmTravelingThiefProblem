#ifndef TTPMUTATIONMETHODS_HPP
#define TTPMUTATIONMETHODS_HPP

#include <vector>

#include "geneticutils.hpp"
#include "ttpindividual.hpp"

namespace TTPMutationMethod
{

/**
 * @brief twoOpt_bitFlip    Uses the 2-Opt method with random cut points
 *                          for the tour component and Bit Flip method with 50% chance
 *                          that a bit be flipped for the picking plan component
 *
 * @param population        Population that will be mutated.
 *
 * @return                  The mutated population.
 */
std::vector< TTPIndividual > twoOpt_bitFlip( const std::vector< TTPIndividual >& population );

}

#endif // TTPMUTATIONMETHODS_HPP

