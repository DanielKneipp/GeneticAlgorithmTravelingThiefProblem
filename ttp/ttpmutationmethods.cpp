#include "ttpmutationmethods.hpp"

namespace TTPMutationMethod
{

std::vector< TTPIndividual > twoOpt_bitFlip( const std::vector< TTPIndividual >& population,
                                             const float alphaProb )
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
                                                                           alphaProb );


        mutatedPopulation.push_back( mutatedIndividual );
    }

    return mutatedPopulation;
}

std::vector< TTPIndividual > twoOpt_bitFlip_likely( const std::vector< TTPIndividual >& population,
                                                    const float alphaProb )
{
    std::vector< TTPIndividual > mutatedPopulation;
    mutatedPopulation.reserve( population.size() );

    for( const TTPIndividual& individual : population )
    {
        TTPIndividual mutatedIndividual = individual;

        float p = GeneticUtils::genRealRandNumber< float >( 0.f, 1.f );

        if( p < 0.65 )          // 65% of chance
        {
            //** Bit flip **//
            mutatedIndividual.features.pickingPlan = MutationMethods::bitFlip< unsigned short >
                                                                             ( individual.features.pickingPlan,
                                                                               alphaProb );
        }
        else if( p > 0.825 )    // 17,5% of chance
        {

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
        }
        else                    // 17,5% of chance
        {
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
                                                                               alphaProb );
        }

        mutatedPopulation.push_back( mutatedIndividual );
    }

    return mutatedPopulation;
}

std::vector< TTPIndividual > doubleBridge_bitFlip( const std::vector< TTPIndividual >& population,
                                                   const float alphaProb )
{
    std::vector< TTPIndividual > mutatedPopulation;
    mutatedPopulation.reserve( population.size() );

    for( const TTPIndividual& individual : population )
    {
        TTPIndividual mutatedIndividual = individual;

        //** Double bridge **//
        // Getting 3 positions that describes the 4 segments.
        // Don't get the last and first city because they should be the first city (1).
        std::vector< std::size_t > positions = GeneticUtils::getNPositions< std::size_t >( 1,
                                                                                           individual.features.tour.size() - 2,
                                                                                           3 );
        std::array< std::size_t, 3 > arrPos;
        std::copy_n( positions.begin(), 3, arrPos.begin() );

        // Permute.
        mutatedIndividual.features.tour = MutationMethods::doubleBridge< unsigned long >
                                                                       ( individual.features.tour, arrPos );

        //** Bit flip **//
        mutatedIndividual.features.pickingPlan = MutationMethods::bitFlip< unsigned short >
                                                                         ( individual.features.pickingPlan,
                                                                           alphaProb );

        mutatedPopulation.push_back( mutatedIndividual );
    }

    return mutatedPopulation;
}

std::vector< TTPIndividual > twoOpt_bitFlip_elitism( const std::vector< TTPIndividual >& population,
                                                     const std::size_t numElites,
                                                     const float alphaProb )
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
                                                                                                   sortedElites.end() ), alphaProb );

    sortedElites.erase( sortedElites.begin() + numElites, sortedElites.end() );

    // Insert the elite solutions group to the selected solutions group.
    mutatedPopulation.insert( mutatedPopulation.end(),
                              sortedElites.begin(),
                              sortedElites.end() );

    return mutatedPopulation;
}

}

