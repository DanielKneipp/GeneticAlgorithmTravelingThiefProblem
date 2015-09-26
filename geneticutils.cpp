#include "geneticutils.hpp"

template< typename T >
T GeneticUtils::genRealRandNumber( const T min, const T max )
{
    // Seed.
    std::random_device rd;
    // Seed used to feed the random number generator.
    std::mt19937 mt( rd() );
    // Note: uniform_real_distribution does [min, max),
    // but we want to do [min, max].
    // Pass the next largest value instead.
    std::uniform_real_distribution< T >dist( min,
                                             std::nextafter( max,
                                                             std::numeric_limits< T >::max() ) );

    return dist( mt );
}


template< typename T >
T GeneticUtils::genRealRandNumber( const T min, const T max )
{
    // Seed.
    std::random_device rd;
    // Seed used to feed the random number generator.
    std::mt19937 mt( rd() );
    // Generate a uniform integer random distribution on [min, max]
    std::uniform_int_distribution< T >dist( min, max );

    return dist( mt );
}
