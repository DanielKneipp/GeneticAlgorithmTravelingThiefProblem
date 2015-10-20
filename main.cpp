#include <iostream>
#include <vector>
#include <string>

#include "ttp/ttpga.hpp"
#include "ttp/ttpindividual.hpp"
#include "ttp/ttpinstance.hpp"

enum ErrorTypes
{
    NUM_ARGS    = -1,
    EXCEPTION   = -2
};

void printHelp()
{
    std::cout << "Usage: GA <TTP instance file> <number of individuals> <number of generations> [output directory]" << std::endl;
}

int main( int argc, char *argv[] )
{
    if( argc < 4 )
    {
        printHelp();
        return ErrorTypes::NUM_ARGS;
    }

    unsigned numIndividuals = 0;
    unsigned numGenerations = 0;
    TTPGA ga;

    try
    {
        numIndividuals = static_cast< unsigned >( std::stoul( argv[ 2 ] ) );
        numGenerations = static_cast< unsigned >( std::stoul( argv[ 3 ] ) );

        TTPInstance problem( argv[ 1 ] );
        if( argc == 5 )
        {
            ga.outputDirectory = argv[ 4 ];
        }
        ga.problem = problem;
        ga.run( numIndividuals, numGenerations );

        std::vector< TTPIndividual > ind = ga.getBestNIndividuals( 1 );
        std::cout << "Best Individual: " << ind[ 0 ].toString() << std::endl;

        std::cout << "Execution Time: " << ga.executionTime.count() << " seconds" << std::endl;
    }
    catch( std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        return ErrorTypes::EXCEPTION;
    }

    return 0;
}

