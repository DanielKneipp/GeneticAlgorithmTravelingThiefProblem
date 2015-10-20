#ifndef SELECTIONMETHODS
#define SELECTIONMETHODS

#include <vector>
#include <algorithm>

#include "../utils/geneticutils.hpp"

namespace SelectionMethod
{

/**
 * @brief tournament            Tournament method. Selects the best individual
 *                              by each tournament of a specific size. The number
 *                              of the tournaments specifies the size of the selected
 *                              population.
 *
 * @param tournamentSize        Size of the tournament.
 *
 * @param newPopulationSize     Size of the selected population.
 *
 * @param population            Population to be selected.
 *
 * @return                      The selected population.
 */
template< class T >
std::vector< T > tournament( const std::vector< T >& population,
                             const std::size_t tournamentSize,
                             const std::size_t newPopulationSize );

/**
 * @brief tournament_elitism    Uses the \ref tournament method to select
 *                              (\ref newPopulationSize - \ref numElites) solutions but
 *                              ensure that \ref numElites best solutions will be kept to
 *                              selected population group.
 *
 * @param tournamentSize        Size of the tournament.
 *
 * @param newPopulationSize     Size of the selected population.
 *
 * @param numElites             Number of elite solutions to be kept.
 *
 * @param population            Population to be selected.
 *
 * @return                      The selected population.
 */
template< class T >
std::vector< T > tournament_elitism( const std::vector< T >& population,
                                     const std::size_t tournamentSize,
                                     const std::size_t newPopulationSize,
                                     const std::size_t numElites );

}


template< class T >
std::vector< T > SelectionMethod::tournament( const std::vector< T >& population,
                                              const std::size_t tournamentSize,
                                              const std::size_t newPopulationSize )
{
    std::vector< T > selectedPopulation;
    selectedPopulation.reserve( newPopulationSize );

    // Note: Position 0 is always the best position of the tournament.
    std::size_t ring[ 2 ];
    std::size_t randPos = 0;

    for( std::size_t i = 0; i < newPopulationSize; i++ )
    {
        randPos = GeneticUtils::genIntRandNumber< std::size_t >( 0, population.size() - 1 );
        ring[ 0 ] = randPos;

        for( std::size_t j = 1; j < tournamentSize; j++ )
        {
            randPos = GeneticUtils::genIntRandNumber< std::size_t >( 0, population.size() - 1 );
            ring[ 1 ] = randPos;

            if( population[ ring[ 1 ] ] > population[ ring[ 0 ] ] )
            {
                ring[ 0 ] = ring[ 1 ];
            }
        }
        selectedPopulation.push_back( population[ ring[ 0 ] ] );
    }

    return selectedPopulation;
}

template< class T >
std::vector< T > SelectionMethod::tournament_elitism( const std::vector< T >& population,
                                                      const std::size_t tournamentSize,
                                                      const std::size_t newPopulationSize,
                                                      const std::size_t numElites )
{
    // Get numElite elite solutions to keep.
    std::vector< T > sortedElites = population;
    std::partial_sort( sortedElites.begin(),
                       sortedElites.begin() + numElites,
                       sortedElites.end(),
                       []( const T& a, const T& b ) -> bool
                       {
                           return a.fitness > b.fitness;
                       });
    sortedElites.erase( sortedElites.begin() + numElites, sortedElites.end() );

    // Use Tournament method to get a selected population
    // (with size of the population - number of elites). The elite
    // solutions are included in the tournament.
    std::vector< T > selectedPopulation = SelectionMethod::tournament( population,
                                                                       tournamentSize,
                                                                       newPopulationSize - numElites );
    // Insert the elite solutions group to the selected solutions group.
    selectedPopulation.insert( selectedPopulation.end(),
                               sortedElites.begin(),
                               sortedElites.end() );

    return selectedPopulation;
}

#endif // SELECTIONMETHODS
