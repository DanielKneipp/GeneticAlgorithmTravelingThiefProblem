#ifndef GENETICUTILS_HPP
#define GENETICUTILS_HPP

#include <random>
#include <limits>
#include <cmath>    // std::nextafter

#include "geneticutils.hpp"

namespace GeneticUtils
{

enum PROBLEM_TYPE
{
    MAXIMIZATION = 1,
    MINIMIZATION = 2
};

template< typename T >
T genRealRandNumber( const T min, const T max );

template< typename T >
T genIntRandNumber( const T min, const T max );

}

#endif // GENETICUTILS_HPP

