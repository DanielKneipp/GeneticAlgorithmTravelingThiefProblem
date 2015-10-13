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

    const unsigned long TOURNAMET_SIZE = 3;
    const unsigned long SELECTION_NUM_ELITES = 2;
    const unsigned long MUTATION_NUM_ELITES = 2;

    std::string stringSpecs = std::to_string( numIndividuals ) +
                              "_" + std::to_string( TOURNAMET_SIZE ) +
                              "_" + std::to_string( SELECTION_NUM_ELITES ) +
                              "_" + std::to_string( MUTATION_NUM_ELITES );

    IndividualRecorder rec;
    rec.setDestinationFile( IndividualRecorder::getSuffixDateTime() + "__" + stringSpecs + ".dat" );

    this->startTimer();

    this->population = this->generatePopulation( numIndividuals );
    this->problem.evaluateIndividuals( this->population );

    for( unsigned i = 0; i < numGenerations; i++ )
    {


        //** Selection Step **//
        this->population = SelectionMethod::tournament_elitism( this->population,
                                                                TOURNAMET_SIZE,
                                                                this->population.size(),
                                                                SELECTION_NUM_ELITES );

        //** Crossover Step **//
        std::vector< TTPIndividual > children = TTPCrossoverMethod::orderBased_alternate( this->population,
                                                                                          1 );
        this->population.insert( this->population.end(), children.begin(), children.end() );
        this->problem.evaluateIndividuals( this->population );
        this->population = GeneticUtils::getBestNIndividuals( this->population, numIndividuals );

        //** Mutation Step **//
        this->population = TTPMutationMethod::twoOpt_bitFlip_elitism( this->population,
                                                                      MUTATION_NUM_ELITES );

        //** Evaluation Step **//
        this->problem.evaluateIndividuals( this->population );

        std::cout << "Iteration " << i << " completed." << std::endl;
        rec.recordIndFitnessToFile( this->getBestNIndividuals( 1 )[ 0 ] );
    }

    this->stopTimer();

    rec.plot( "plotGAData.gnu", stringSpecs );
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

        GeneticUtils::shuffleVector( baseTour.begin() + 1, baseTour.end() - 1 );
        individual.features.tour = baseTour;


        //** Generating KP component **//
        individual.features.pickingPlan.reserve( this->problem.numItems );
        for( unsigned long j = 0; j < this->problem.numItems; j++ )
        {
//            individual.features.pickingPlan.push_back( GeneticUtils::genIntRandNumber< unsigned short >( 0, 1 ) );
            individual.features.pickingPlan.push_back( 0 );
        }


        population.push_back( individual );
    }

    return population;
}
