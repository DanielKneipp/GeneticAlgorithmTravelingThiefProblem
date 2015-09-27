#ifndef GENETICUTILS_HPP
#define GENETICUTILS_HPP

#include <random>
#include <limits>
#include <cmath>    // std::nextafter

#include "geneticutils.hpp"

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
T genRealRandNumber( const T min, const T max );

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
T genIntRandNumber( const T min, const T max );

}

#endif // GENETICUTILS_HPP

