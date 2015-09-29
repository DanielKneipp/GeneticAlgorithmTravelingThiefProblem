#include "ttpga.hpp"

TTPGA::TTPGA() {}

void TTPGA::run( unsigned numIndividuals,
                 unsigned numGenerations )
{
    if( numIndividuals % 2 != 0 )
    {
        throw std::invalid_argument( "numIndividuals must to be an even number" );
    }
    if( !this->problem.isLoaded )
    {
        throw std::logic_error( "Problem is not loaded yet!" );
    }

    this->startTimer();

    this->population = this->generatePopulation( numIndividuals );

    for( unsigned i = 0; i < numGenerations; i++ )
    {
        //** Evaluation Step **//
        this->problem.evaluateIndividuals( this->population );

        //** Selection Step **//
        this->population = SelectionMethod::tournament( 3,
                                                        this->population.size(),
                                                        this->population );

        //** Crossing Step **//


        //** Mutation Step **//
        this->population = TTPMutationMethod::twoOpt_bitFlip( this->population );
    }
    this->problem.evaluateIndividuals( this->population );

    this->stopTimer();
}

std::vector< TTPIndividual > TTPGA::generatePopulation( unsigned numIndividuals )
{
    std::vector< TTPIndividual > population;
    population.reserve( numIndividuals );

    std::vector< unsigned long > baseTour( this->problem.numCities + 1 );
    std::iota( baseTour.begin(), baseTour.end(), 1 );
    baseTour[ this->problem.numCities ] = 1;

    for( unsigned i = 0; i < numIndividuals; i++ )
    {
        TTPIndividual individual;


        //** Generating TSP component **//
        individual.features.tour.reserve( this->problem.numCities + 1 );

        std::random_shuffle( baseTour.begin() + 1, baseTour.end() - 1 );
        individual.features.tour = baseTour;


        //** Generating KP component **//
        individual.features.pickingPlan.reserve( this->problem.numItems );
        for( unsigned long j = 0; j < this->problem.numItems; j++ )
        {
            individual.features.pickingPlan.push_back( GeneticUtils::genIntRandNumber< unsigned short >( 0, 1 ) );
        }


        population.push_back( individual );
    }

    return population;
}
