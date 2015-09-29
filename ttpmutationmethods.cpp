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
            if( randNum < 0.5 )
            {
                mutatedIndividual.features.pickingPlan[ i ] ^= ( unsigned short )( 1 );
            }
        }

        mutatedPopulation.push_back( mutatedIndividual );
    }

    return mutatedPopulation;
}
