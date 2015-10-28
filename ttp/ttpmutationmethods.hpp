#ifndef TTPMUTATIONMETHODS_HPP
#define TTPMUTATIONMETHODS_HPP

#include <vector>
#include <array>
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
 * @param alphaProb         Probability of a item be picked or removed from the
 *                          knapsack.
 *
 * @return                  The mutated population.
 */
std::vector< TTPIndividual > twoOpt_bitFlip( const std::vector< TTPIndividual >& population,
                                             const float alphaProb = 0.001f );

/**
 * @brief twoOpt_bitFlip_likely     Same as \ref twoOpt_bitFlip() but the KP component
 *                                  has 65% chance to be muted, the TSP component has
 *                                  17,5% chance to be mutated and it has 17,5% chance 
 *                                  of both components be mutated.
 *
 * @param population                Population that will be mutated.
 *
 * @param alphaProb                 Probability of a item be picked or removed from the
 *                                  knapsack.
 *
 * @return                          The mutated population.
 */
std::vector< TTPIndividual > twoOpt_bitFlip_likely( const std::vector< TTPIndividual >& population,
                                                    const float alphaProb = 0.001f );

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
 * @param alphaProb                 Probability of a item be picked or removed from the
 *                                  knapsack.
 *
 * @return                          The mutated population.
 */
std::vector< TTPIndividual > twoOpt_bitFlip_elitism( const std::vector< TTPIndividual >& population,
                                                     const std::size_t numElites,
                                                     const float alphaProb = 0.001f );

std::vector< TTPIndividual > doubleBridge_bitFlip( const std::vector< TTPIndividual >& population,
                                                   const float alphaProb = 0.001f );

}

#endif // TTPMUTATIONMETHODS_HPP

