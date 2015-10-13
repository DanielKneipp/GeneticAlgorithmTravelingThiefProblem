#ifndef MUTATIONMETHODS_HPP
#define MUTATIONMETHODS_HPP

#include <vector>

#include "../utils/geneticutils.hpp"

namespace MutationMethods
{

/**
 * @brief bitFlip           Flip the value of a position of \ref features
 *                          with a probability specified by \ref probability .
 *
 * @param features          Array of integer values with range of [0, 1].
 *
 * @param probability       Probability of a given value be flipped.
 *
 * @return                  The new mutated array.
 */
template< typename T >
std::vector< T > bitFlip( const std::vector< T >& features, float probability );

/**
 * @brief twoOpt            Generate a new array of features with the values
 *                          inside the range specified bi \ref beginPoint and
 *                          \ref endPoint writed in reverse order.
 *
 * @param features          Array of features.
 *
 * @param beginPoint        Begin of the sub-array that will be writed in reverse
 *                          order.
 *
 * @param endPoint          End of the sub-array that will be writed in reverse
 *                          order.
 *
 * @return                  The mutated array.
 */
template< typename T_f, typename T_idx >
std::vector< T_f > twoOpt( const std::vector< T_f >& features,
                           T_idx beginPoint,
                           T_idx endPoint );

/**
 * @brief swapPositions     Swap the fetures with his positions specified by
 *                          \ref beginPoint and \ref endPoint.
 *
 * @param features          Array of features.
 *
 * @param beginPoint        The position of some feature that will be swapped.
 *
 * @param endPoint          The position of another feature that will be swapped.
 *
 * @return                  The mutated array.
 */
template< typename T_f, typename T_idx >
std::vector< T_f > swapPositions( const std::vector< T_f >& features,
                                  T_idx beginPoint,
                                  T_idx endPoint );

}

#include "mutationmethods.cpp"

#endif // MUTATIONMETHODS_HPP

