#include "ttpmutationmethods.hpp"


std::vector< TTPIndividual > TTPMutationMethod::twoOpt_bitFlip( const std::vector< TTPIndividual >& population )
{
    std::vector< TTPIndividual > mutatedPopulation;
    mutatedPopulation.reserve( population.size() );

    for( const TTPIndividual& individual : population )
    {
        TTPIndividual mutatedIndividual = individual;

        //** 2-opt **//
        // Generating start and end cut points.
        // Don't get the last and first city because they should be the first city (1).
        unsigned long beginPoint = GeneticUtils::genIntRandNumber< unsigned long >( 1,
                                                                                    individual.features.tour.size() - 3 );
        unsigned long endPoint = GeneticUtils::genIntRandNumber< unsigned long >( beginPoint + 1,
                                                                                  individual.features.tour.size() - 2 );
        // Swap.
        for( unsigned long i = beginPoint; i <= endPoint; i++ )
        {
            mutatedIndividual.features.tour[ i ] = individual.features.tour[ endPoint - ( i - beginPoint ) ];
        }


        //** Bit flip **//
        for( unsigned long i = 0; i < mutatedIndividual.features.pickingPlan.size(); i++ )
        {
            float randNum = GeneticUtils::genRealRandNumber< float >( 0.f, 1.f );
            // TODO: The better the fitness, the less likely to turn the bit.
            if( randNum < 0.001 )
            {
                mutatedIndividual.features.pickingPlan[ i ] ^= ( unsigned short )( 1 );
            }
        }

        mutatedPopulation.push_back( mutatedIndividual );
    }

    return mutatedPopulation;
}

std::vector< TTPIndividual > TTPMutationMethod::twoOpt_bitFlip_elitism( const unsigned long numElites,
                                                                        const std::vector< TTPIndividual >& population )
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
    std::vector< TTPIndividual > mutatedPopulation = TTPMutationMethod::twoOpt_bitFlip( std::vector< TTPIndividual >( sortedElites.begin() + numElites,
                                                                                                                      sortedElites.end() ) );

    sortedElites.erase( sortedElites.begin() + numElites, sortedElites.end() );

    // Insert the elite solutions group to the selected solutions group.
    mutatedPopulation.insert( mutatedPopulation.end(),
                              sortedElites.begin(),
                              sortedElites.end() );

    return mutatedPopulation;
}
