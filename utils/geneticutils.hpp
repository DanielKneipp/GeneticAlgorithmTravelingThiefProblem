#ifndef GENETICUTILS_HPP
#define GENETICUTILS_HPP

#include <random>
#include <vector>
#include <array>
#include <limits>
#include <algorithm>
#include <cmath>        // std::nextafter()
#include <numeric>      // std::iota()

namespace GeneticUtils
{

/** Seed. */
static std::random_device rd;
/** Seed being used to feed the random number generator. */
static std::mt19937 mt = std::mt19937( rd() );

/**
 * @brief The PROBLEM_TYPE enum specifies if the problem is of
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
 *                              the sub-vector that will be shuffled.
 *
 * @param end                   The iterator positioned at the end of
 *                              the sub-vector that will be shuffled.
 */
template< class T_it >
void shuffleVector( T_it begin, T_it end )
{
    std::shuffle( begin, end, mt );
}

/**
 * @brief getBestNIndividuals       Used to get the best individuals in the
 *                                  population. The function that compares two
 *                                  individuals returns \c true if some individual
 *                                  \c a have a fitness greater than other individual
 *                                  \c b, in that case the individuals with higher
 *                                  fitness will be returned in the first positions.
 *
 * @param population                The array of individuals.
 *
 * @param numIndividuals            Number of individuals that will be returned.
 *
 * @return                          The best individuals in the population.
 */
template< class T_ind >
std::vector< T_ind > getBestNIndividuals( const std::vector< T_ind >& population,
                                          const unsigned numIndividuals )
{
    std::vector< T_ind > partialSortedPopulation = population;
    std::partial_sort( partialSortedPopulation.begin(),
                       partialSortedPopulation.begin() + numIndividuals,
                       partialSortedPopulation.end(),
                       []( const T_ind& a, const T_ind& b ) -> bool
                       {
                           return a.fitness > b.fitness;
                       });

    return std::vector< T_ind >( partialSortedPopulation.begin(),
                                 partialSortedPopulation.begin() + numIndividuals );
}

/**
 * @brief getBestNIndividuals       Used to get the individuals in the
 *                                  population based on a comparative criteria.
 *
 * @param population                The array of individuals.
 *
 * @param numIndividuals            Number of individuals that will be returned.
 *
 * @param comp                      Function that will be used to compare two individuals.
 *
 * @return                          The best individuals in the population.
 */
template< class T_ind, class Comapre >
std::vector< T_ind > getNIndividuals( const std::vector< T_ind >& population,
                                      const unsigned numIndividuals,
                                      Comapre comp )
{
    std::vector< T_ind > partialSortedPopulation = population;
    std::partial_sort( partialSortedPopulation.begin(),
                       partialSortedPopulation.begin() + numIndividuals,
                       partialSortedPopulation.end(),
                       comp);

    return std::vector< T_ind >( partialSortedPopulation.begin(),
                                 partialSortedPopulation.begin() + numIndividuals );
}

/**
 * @brief getWorstNIndividuals      Used to get the worst individuals in the
 *                                  population. The function that compares two
 *                                  individuals returns \c true if some individual
 *                                  \c a have a fitness lower than other individual
 *                                  \c b, in that case the individuals with lower
 *                                  fitness will be returned in the first positions.
 *
 * @param population                The array of individuals.
 *
 * @param numIndividuals            Number of individuals that will be returned.
 *
 * @return                          The worst individuals in the population.
 */
template< class T_ind >
std::vector< T_ind > getWorstNIndividuals( const std::vector< T_ind >& population,
                                           const unsigned numIndividuals )
{
    std::vector< T_ind > partialSortedPopulation = population;
    std::partial_sort( partialSortedPopulation.begin(),
                       partialSortedPopulation.begin() + numIndividuals,
                       partialSortedPopulation.end(),
                       []( const T_ind& a, const T_ind& b ) -> bool
                       {
                           return a.fitness < b.fitness;
                       });

    return std::vector< T_ind >( partialSortedPopulation.begin(),
                                 partialSortedPopulation.begin() + numIndividuals );
}

/**
 * @brief sortIndividuals           Used to ordering the population.
 *                                  The function that compares two
 *                                  individuals returns \c true if some individual
 *                                  \c a have a fitness greater than other individual
 *                                  \c b, in that case the individuals with higher
 *                                  fitness will be returned in the first positions.
 *
 * @param population                The array of individuals.
 *
 * @param numIndividuals            Number of individuals that will be returned.
 *
 * @return                          The ordered population.
 */
template< class T_ind >
std::vector< T_ind > sortIndividuals( const std::vector< T_ind >& population )
{
    std::vector< T_ind > sortedPopulation = population;
    std::sort( sortedPopulation.begin(),
               sortedPopulation.end(),
               []( const T_ind& a, const T_ind& b ) -> bool
               {
                   return a.fitness > b.fitness;
               });

    return sortedPopulation;
}

/**
 * @brief sortIndividuals           Used to ordering the population.
 *
 * @param population                The array of individuals.
 *
 * @param numIndividuals            Number of individuals that will be returned.
 *
 * @param comp                      Function that will be used to compare two individuals.
 *
 * @return                          The ordered population.
 */
template< class T_ind, class Compare >
std::vector< T_ind > sortIndividuals( const std::vector< T_ind >& population,
                                      Compare comp )
{
    std::vector< T_ind > sortedPopulation = population;
    std::sort( sortedPopulation.begin(),
               sortedPopulation.end(),
               comp);

    return sortedPopulation;
}

/**
 * @brief getNPositions     Get N sorted values in the range [{@ref startPoint},
 *                          {@ref endPoint}] that will be used as indexes.
 *
 * @param startPoint        The lowest possible value.
 *
 * @param endPoint          The highest possible value.
 *
 * @param numPositions      The number of positions that is wanted.
 *
 * @return                  A sorted (lowest to highest) array with the indexes.
 */
template< typename T >
std::vector< T > getNPositions( const T startPoint,
                                const T endPoint,
                                unsigned numPositions = 1 )
{
    std::vector< T > allPostitions( endPoint - startPoint + 1 );
    std::iota( allPostitions.begin(), allPostitions.end(), startPoint );

    shuffleVector( allPostitions.begin(), allPostitions.end() );

    std::vector< T > selectedPositions( allPostitions.begin(),
                                        allPostitions.begin() + numPositions );

    std::sort( selectedPositions.begin(), selectedPositions.end() );

    return selectedPositions;
}

/**
 * @brief The valueWithIdx structure can be used to store some value
 *        together with some index value.
 */
template< typename T >
struct valueWithIdx
{
    /** Index of the value. */
    std::size_t index;
    /** The value it self. */
    T value;

    /**
     * @brief valueWithIdx  Constructor.
     */
    valueWithIdx() : index( 0 ) {}
    /**
     * @brief valueWithIdx  Constructor with initialization.
     *
     * @param i             The index.
     *
     * @param v             The value.
     */
    valueWithIdx( const std::size_t i, const T v )
    {
        this->index = i;
        this->value = v;
    }
    /**
     * @brief operator <    Verify if the index of this item
     *                      is less than the item {@ref a}.
     *
     * @param a             The other item.
     *
     * @return              \c true , if this item have a index less
     *                      than the index of the item passed as parameter,
     *                      \c false , otherwise.
     */
    bool operator < ( const valueWithIdx& a ) const
    {
        return this->index < a.index;
    }
};

}

#endif // GENETICUTILS_HPP

