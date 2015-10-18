#include "ttpcrossovermethods.hpp"

namespace TTPCrossoverMethod
{

std::vector< TTPIndividual > orderBased_alternate( const std::vector< TTPIndividual >& population,
                                                   const unsigned numCutPoints )
{
    std::vector< TTPIndividual > children( population.size() );
    std::vector< TTPIndividual > shuffledPopulation = population;

    GeneticUtils::shuffleVector( shuffledPopulation.begin(), shuffledPopulation.end() );

    const std::size_t numItems = population[ 0 ].features.pickingPlan.size();

    for( std::size_t i = 0; i < population.size(); i = i + 2 )
    {
        //** Alternate with n cut points - KP-component **//
        std::vector< std::size_t > cutPoints = GeneticUtils::getNPositions< std::size_t >
                                                                          ( 0, numItems - 1, numCutPoints );

        std::array< std::vector< unsigned short >, 2 > childrenKPComponent = CrossoverMethod::alternateNCutPoints< unsigned short,
                                                                                                                   std::size_t >
                                                                                                                 ( shuffledPopulation[ i ].features.pickingPlan,
                                                                                                                   shuffledPopulation[ i + 1 ].features.pickingPlan,
                                                                                                                   cutPoints );


        //** Order-based crossover - TSP-component **//
        // Exclude the first and the last city (1) from the operation.
        std::vector< unsigned long > tspP1ToCross = shuffledPopulation[ i ].features.tour;
        tspP1ToCross.erase( tspP1ToCross.begin() );
        tspP1ToCross.pop_back();
        std::vector< unsigned long > tspP2ToCross = shuffledPopulation[ i + 1 ].features.tour;
        tspP2ToCross.erase( tspP2ToCross.begin() );
        tspP2ToCross.pop_back();
        std::array< std::vector< unsigned long >, 2 > childrenTSPComponent = CrossoverMethod::orderBased< unsigned long >
                                                                                                        ( tspP1ToCross,
                                                                                                          tspP2ToCross );


        children[ i ].features.pickingPlan = childrenKPComponent[ 0 ];
        children[ i + 1 ].features.pickingPlan = childrenKPComponent[ 1 ];

        children[ i ].features.tour.push_back( 1 );
        children[ i ].features.tour.insert( children[ i ].features.tour.end(),
                                            childrenTSPComponent[ 0 ].begin(),
                                            childrenTSPComponent[ 0 ].end() );
        children[ i ].features.tour.push_back( 1 );
        children[ i + 1 ].features.tour.push_back( 1 );
        children[ i + 1 ].features.tour.insert( children[ i + 1 ].features.tour.end(),
                                                childrenTSPComponent[ 1 ].begin(),
                                                childrenTSPComponent[ 1 ].end() );
        children[ i + 1 ].features.tour.push_back( 1 );
    }

    return children;
}

}
