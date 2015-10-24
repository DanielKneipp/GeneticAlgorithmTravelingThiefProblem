#ifndef MUTATIONMETHODS_HPP
#define MUTATIONMETHODS_HPP

#include <vector>
#include <array>

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
 *                          \ref endPoint written in reverse order.
 *
 * @param features          Array of features.
 *
 * @param beginPoint        Begin of the sub-array that will be written in reverse
 *                          order.
 *
 * @param endPoint          End of the sub-array that will be written in reverse
 *                          order.
 *
 * @return                  The mutated array.
 */
template< typename T_f, typename T_idx >
std::vector< T_f > twoOpt( const std::vector< T_f >& features,
                           T_idx beginPoint,
                           T_idx endPoint );

/**
 * @brief swapPositions     Swap the features with his positions specified by
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

/**
 * @brief doubleBridge      Perform a mutation using double-bridge operator.
 *
 * @param features          Array of features.
 *
 * @param positions         Array of 3 positions that specifies the 4 segments
 *                          necessary to perform the mutation.
 *
 * @return                  The mutated array.
 */
template< typename T_f >
std::vector< T_f > doubleBridge( const std::vector< T_f >& features,
                                 std::array< std::size_t, 3 >& positions );

/**
 * @brief generic_elitism   Used to perform any mutation method with elitism.
 *                          The elite solutions aren't included in the mutation 
 *                          procedure.
 *
 * @param population        The set of individuals.
 *
 * @param numElites         Number of elite solutions to be kept.
 *
 * @param func              The mutation method. Must receive an array of 
 *                          individuals as an input parameter (population) and
 *                          return the same type (mutated population).
 */
template< class F, class T_i >
std::vector< T_i > generic_elitism( const std::vector< T_i >& population,
                                    const std::size_t numElites,
                                    F&& func );
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
std::vector< T_f > MutationMethods::swapPositions( const std::vector< T_f >& features,
                                                   T_idx beginPoint,
                                                   T_idx endPoint )
{
    std::vector< T_f > mutatedFeatures = features;

    mutatedFeatures[ beginPoint ] = features[ endPoint ];
    mutatedFeatures[ endPoint ] = features[ beginPoint ];

    return mutatedFeatures;
}

template< typename T_f >
std::vector< T_f > MutationMethods::doubleBridge( const std::vector< T_f >& features,
                                                  std::array< std::size_t, 3 >& positions )
{
    // Minimum size of features array = 5 -> positions = (1, 2, 3).
    std::vector< T_f > mutatedFeatures = features;

    std::size_t i = positions[ 0 ];
    for( std::size_t j = positions[ 2 ]; j < features.size() - 1; i++, j++ )
    {
        mutatedFeatures[ i ] = features[ j ];
    }
    for( std::size_t j = positions[ 1 ]; j < positions[ 2 ]; i++, j++ )
    {
        mutatedFeatures[ i ] = features[ j ];
    }
    for( std::size_t j = positions[ 0 ]; j < positions[ 1 ]; i++, j++ )
    {
        mutatedFeatures[ i ] = features[ j ];
    }

    return mutatedFeatures;
}

template< class F, class T_i >
std::vector< T_i > MutationMethods::generic_elitism( const std::vector< T_i >& population,
                                                     const std::size_t numElites,
                                                     F&& func )
{
    // Get numElite elite solutions to keep.
    std::vector< T_i > sortedElites = population;
    std::partial_sort( sortedElites.begin(),
                       sortedElites.begin() + numElites,
                       sortedElites.end(),
                       []( const T_i& a, const T_i& b ) -> bool
                       {
                           return a.fitness > b.fitness;
                       });

    // Use some method to get a mutated population
    // (with size of the population - number of elites). The elite solutions
    // aren't included in the mutation procedure.
    std::vector< T_i > mutatedPopulation = func( std::vector< T_i >( sortedElites.begin() + numElites,
                                                                     sortedElites.end() ) );

    sortedElites.erase( sortedElites.begin() + numElites, sortedElites.end() );

    // Insert the elite solutions group to the selected solutions group.
    mutatedPopulation.insert( mutatedPopulation.end(),
                              sortedElites.begin(),
                              sortedElites.end() );

    return mutatedPopulation;
}

#endif // MUTATIONMETHODS_HPP
