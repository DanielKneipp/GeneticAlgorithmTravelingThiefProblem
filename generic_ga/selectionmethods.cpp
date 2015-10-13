#include "selectionmethods.hpp"

template< class T >
std::vector< T > SelectionMethod::tournament( const std::vector< T >& population,
                                              const unsigned long tournamentSize,
                                              const unsigned long newPopulationSize )
{
    std::vector< T >selectedPopulation;
    selectedPopulation.reserve( newPopulationSize );

    unsigned long ring[ tournamentSize ];

    unsigned long best = 0;
    unsigned long randPos = 0;

    for( unsigned long i = 0; i < newPopulationSize; i++ )
    {
        randPos = GeneticUtils::genIntRandNumber< unsigned long >( 0, population.size() - 1 );
        ring[ 0 ] = randPos;
        best = 0;

        for( unsigned long j = 1; j < tournamentSize; j++ )
        {
            randPos = GeneticUtils::genIntRandNumber< unsigned long >( 0, population.size() - 1 );
            ring[ j ] = randPos;

            if( population[ ring[ j ] ] > population[ ring[ best ] ] )
            {
                best = j;
            }
        }
        selectedPopulation.push_back( population[ best ] );
    }

    return selectedPopulation;
}

template< class T >
std::vector< T > SelectionMethod::tournament_elitism( const std::vector< T >& population,
                                                      const unsigned long tournamentSize,
                                                      const unsigned long newPopulationSize,
                                                      const unsigned long numElites )
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
