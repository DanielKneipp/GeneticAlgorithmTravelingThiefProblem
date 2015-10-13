#include "mutationmethods.hpp"

namespace MutationMethods
{

template< typename T >
std::vector< T > bitFlip( const std::vector< T >& features, float probability )
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
std::vector< T_f > twoOpt( const std::vector< T_f >& features,
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

}
