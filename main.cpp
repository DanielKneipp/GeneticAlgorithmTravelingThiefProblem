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
              << " <TTPGA-config-file>" 
              << " [output-directory [standard-output]]" << std::endl;
}

int main( int argc, char *argv[] )
{
    if( argc < 3 )
    {
        printHelp();
        return ErrorTypes::NUM_ARGS;
    }

    TTPGA ga;

    std::streambuf* stcout = std::cout.rdbuf();
    std::ofstream coutFile;

    if( argc >= 5 )
    {
        try
        {
            coutFile = std::ofstream( argv[ 4 ], std::ios::app );
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
        TTPGAConfig gaC1 = TTPGAConfig::readTTPGAConfigFromFile( argv[ 2 ] );

        ga.gaConfig = gaC1;

        TTPInstance problem( argv[ 1 ] );

        std::cout << "Problem: " << problem.probFileName << std::endl;
        std::cout << "GA configurations: \n" << gaC1.toString() << std::endl;

        if( argc >= 4 )
        {
            ga.outputDirectory = argv[ 3 ];
        }

        ga.problem = problem;
        ga.run( gaC1.NUM_INDIVIDUALS, gaC1.NUM_GENERATIONS );

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

