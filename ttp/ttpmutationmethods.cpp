#include "ttpmutationmethods.hpp"

namespace TTPMutationMethod
{

std::vector< TTPIndividual > twoOpt_bitFlip( const std::vector< TTPIndividual >& population )
{
    std::vector< TTPIndividual > mutatedPopulation;
    mutatedPopulation.reserve( population.size() );

    for( const TTPIndividual& individual : population )
    {
        TTPIndividual mutatedIndividual = individual;

        //** 2-opt **//
        // Generating start and end cut points.
        // Don't get the last and first city because they should be the first city (1).
        std::size_t beginPoint = GeneticUtils::genIntRandNumber< std::size_t >( 1,
                                                                                    individual.features.tour.size() - 3 );
        std::size_t endPoint = GeneticUtils::genIntRandNumber< std::size_t >( beginPoint + 1,
                                                                                  individual.features.tour.size() - 2 );
        // Reverse.
        mutatedIndividual.features.tour = MutationMethods::twoOpt< unsigned long, std::size_t >
                                                                 ( individual.features.tour,
                                                                   beginPoint,
                                                                   endPoint );

        //** Bit flip **//
        mutatedIndividual.features.pickingPlan = MutationMethods::bitFlip< unsigned short >
                                                                         ( individual.features.pickingPlan,
                                                                           0.001f );

        mutatedPopulation.push_back( mutatedIndividual );
    }

    return mutatedPopulation;
}

std::vector< TTPIndividual > twoOpt_bitFlip_elitism( const std::vector< TTPIndividual >& population,
                                                     const unsigned long numElites )
{
    // Get numElite elite solutions to keep.
    std::vector< TTPIndividual > sortedElites = population;
    std::partial_sort( sortedElites.begin(),
                       sortedElites.begin() + numElites,
                       sortedElites.end(),
                       []( const TTPIndividual& a, const TTPIndividual& b ) -> bool
                       {
                           return a.fitness > b.fitness;
                       });

    // Use Tow-opt with Bit Flip method to get a mutated population
    // (with size of the population - number of elites). The elite solutions
    // aren't included in the mutation procedure.
    std::vector< TTPIndividual > mutatedPopulation = twoOpt_bitFlip( std::vector< TTPIndividual >( sortedElites.begin() + numElites,
                                                                                                   sortedElites.end() ) );

    sortedElites.erase( sortedElites.begin() + numElites, sortedElites.end() );

    // Insert the elite solutions group to the selected solutions group.
    mutatedPopulation.insert( mutatedPopulation.end(),
                              sortedElites.begin(),
                              sortedElites.end() );

    return mutatedPopulation;
}

}

