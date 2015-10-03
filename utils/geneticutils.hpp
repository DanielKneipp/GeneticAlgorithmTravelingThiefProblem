#ifndef GENETICUTILS_HPP
#define GENETICUTILS_HPP

#include <random>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>    // std::nextafter

namespace GeneticUtils
{

/// Seed.
static std::random_device rd;
/// Seed being used to feed the random number generator.
static std::mt19937 mt = std::mt19937( rd() );

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
    // Generate a uniform integer random distribution on [min, max]
    std::uniform_int_distribution< T >dist( min, max );

    return dist( mt );
}

/**
 * @brief shuffleVector         Used to shuffle a std::vector.
 *
 * @param begin                 The iterator positioned at the start of
 *                              the subvector that will be shuffled.
 *
 * @param end                   The iterator positioned at the end of
 *                              the subvector that will be shuffled.
 */
template< class it_T >
void shuffleVector( it_T begin, it_T end )
{
    std::shuffle( begin, end, mt );
}

}

#endif // GENETICUTILS_HPP

