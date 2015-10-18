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


template< typename T >
std::vector< T > MutationMethods::bitFlip( const std::vector< T >& features, 
                                           float probability )
{
    std::vector< T > mutatedFeatures = features;

    for( auto&& i : mutatedFeatures )
    {
        float randNum = GeneticUtils::genRealRandNumber< float >( 0.f, 1.f );
        if( randNum < probability )
        {
            i ^= 1;
        }
    }

    return mutatedFeatures;
}

template< typename T_f, typename T_idx >
std::vector< T_f > MutationMethods::twoOpt( const std::vector< T_f >& features,
                                            T_idx beginPoint,
                                            T_idx endPoint )
{
    std::vector< T_f > mutatedFeatures = features;

    for( T_idx i = beginPoint; i <= endPoint; i++ )
    {
        mutatedFeatures[ i ] = features[ endPoint - ( i - beginPoint ) ];
    }

    return mutatedFeatures;
}

template< typename T_f, typename T_idx >
std::vector< T_f > swapPositions( const std::vector< T_f >& features,
                                  T_idx beginPoint,
                                  T_idx endPoint )
{
    std::vector< T_f > mutatedFeatures = features;

    mutatedFeatures[ beginPoint ] = features[ endPoint ];
    mutatedFeatures[ endPoint ] = features[ beginPoint ];

    return mutatedFeatures;
}

#endif // MUTATIONMETHODS_HPP
