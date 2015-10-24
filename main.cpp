#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>

#include "ttp/ttpga.hpp"
#include "ttp/ttpindividual.hpp"
#include "ttp/ttpinstance.hpp"

#include "utils/individualrecorder.hpp"

enum ErrorTypes
{
    NUM_ARGS    = -1,
    EXCEPTION   = -2
};

void printHelp()
{
    std::cout << "Usage: GA <TTP-instance-file>" 
              << " <number-of-individuals>" 
              << " <number-of-generations>"
              << " [output-directory [standard-output]]" << std::endl;
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

    std::streambuf* stcout = std::cout.rdbuf();
    std::ofstream coutFile;

    if( argc >= 6 )
    {
        try
        {
            coutFile = std::ofstream( argv[ 5 ], std::ios::app );
            std::cout.rdbuf( coutFile.rdbuf() );
        }
        catch( std::exception& e )
        {
            std::cerr << e.what() << std::endl;
            return ErrorTypes::EXCEPTION;
        }
    }
    
    std::cout << "===============================" << std::endl
              << "------ EXECUTION STARTED ------" << std::endl;

    std::cout << "Date and time: " << IndividualRecorder::getSuffixDateTime() << std::endl;

    try
    {
        numIndividuals = static_cast< unsigned >( std::stoul( argv[ 2 ] ) );
        numGenerations = static_cast< unsigned >( std::stoul( argv[ 3 ] ) );

        TTPGAConfig gaC1;
        gaC1.TOURNAMET_SIZE                  = 2;
        gaC1.TOURNAMET_SIZE_CROSSOVER        = 2;
        gaC1.SELECTION_NUM_ELITES            = static_cast< unsigned long >( numIndividuals * 0.1 );
        gaC1.SELECTION_NUM_ELITES_CROSSOVER  = static_cast< unsigned long >( numIndividuals * 0.1 );
        gaC1.MUTATION_NUM_ELITES             = static_cast< unsigned long >( numIndividuals * 0.1 );
        gaC1.NUM_CUT_POINTS                  = 1;
        gaC1.ALPHA_PROBABILITY               = 0.005f;
        gaC1.CONFIG_NAME                     = "GA1";

        std::cout << "GA configurations: \n" << gaC1.toString() << std::endl;

        ga.gaConfig = gaC1;

        TTPInstance problem( argv[ 1 ] );

        std::cout << "Problem: " << problem.probFileName << std::endl;

        if( argc >= 5 )
        {
            ga.outputDirectory = argv[ 4 ];
        }

        ga.problem = problem;
        ga.run( numIndividuals, numGenerations );

        std::vector< TTPIndividual > ind = ga.getBestNIndividuals( 1 );
        std::cout << "Best Individual: " << ind[ 0 ].toString() << std::endl;

        std::cout << "Total Execution Time: " << std::chrono::duration_cast< std::chrono::milliseconds >
                                                                           ( ga.executionTime ).count() 
                                              << " milliseconds" << std::endl;
    }
    catch( std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        return ErrorTypes::EXCEPTION;
    }

    std::cout << "------  EXECUTION DONE  -------" << std::endl
              << "===============================" << std::endl;

    std::cout.rdbuf( stcout );

    return 0;
}

