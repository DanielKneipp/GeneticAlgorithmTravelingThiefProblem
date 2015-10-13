#ifndef TTPMUTATIONMETHODS_HPP
#define TTPMUTATIONMETHODS_HPP

#include <vector>
#include <algorithm>

#include "../utils/geneticutils.hpp"

#include "../generic_ga/mutationmethods.hpp"

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

/**
 * @brief twoOpt_bitFlip_elitism    Uses the \ref twoOpt_bitFlip() method to mutate
 *                                  the population but ensuring that \ref numElites
 *                                  best individuals will be kept unchanged.
 *
 * @param numElites                 Number of elite solutions that will be kept
 *                                  unchanged.
 *
 * @param population                The population that will be mutated.
 *
 * @return                          The mutated population.
 */
std::vector< TTPIndividual > twoOpt_bitFlip_elitism( const std::vector< TTPIndividual >& population,
                                                     const unsigned long numElites );

}

#endif // TTPMUTATIONMETHODS_HPP

