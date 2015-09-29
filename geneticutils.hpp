#ifndef GENETICUTILS_HPP
#define GENETICUTILS_HPP

#include <random>
#include <limits>
#include <cmath>    // std::nextafter

namespace GeneticUtils
{

/**
 * @brief The PROBLEM_TYPE enum especifies if the problem is of
 *        minimization or maximization.
 */
enum PROBLEM_TYPE
{
    MAXIMIZATION,
    MINIMIZATION
};

/**
 * @brief genRealRandNumber     Generate a random real number between
 *                              inside the range [min, max].
 *
 * @param min                   Lowest value that can be generated.
 *
 * @param max                   Highest value that can be generated.
 *
 * @return                      The random real number generated.
 */
template< typename T >
T genRealRandNumber( const T min, const T max )
{
    // Seed.
    std::random_device rd;
    // Seed being used to feed the random number generator.
    std::mt19937 mt( rd() );
    // Note: uniform_real_distribution does [min, max),
    // but we want to do [min, max].
    // Pass the next largest value instead.
    std::uniform_real_distribution< T >dist( min,
                                             std::nextafter( max,
                                                             std::numeric_limits< T >::max() ) );

    return dist( mt );
}

/**
 * @brief genIntRandNumber      Generate a random integer number between
 *                              inside the range [min, max].
 *
 * @param min                   Lowest value that can be generated.
 *
 * @param max                   Highest value that can be generated.
 *
 * @return                      The random integer number generated.
 */
template< typename T >
T genIntRandNumber( const T min, const T max )
{
    // Seed.
    std::random_device rd;
    // Seed being used to feed the random number generator.
    std::mt19937 mt( rd() );
    // Generate a uniform integer random distribution on [min, max]
    std::uniform_int_distribution< T >dist( min, max );

    return dist( mt );
}

}

#endif // GENETICUTILS_HPP

