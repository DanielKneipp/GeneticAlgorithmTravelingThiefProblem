#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <cmath>    // std::sqrt()

#include "ttp/ttpga.hpp"
#include "ttp/ttpindividual.hpp"
#include "ttp/ttpinstance.hpp"

#include "utils/individualrecorder.hpp"
#include "utils/geneticutils.hpp"

enum ErrorTypes
{
    NUM_ARGS    = -1,
    EXCEPTION   = -2
};

void printHelp()
{
    std::cout << "Usage: GA <TTP-instance-file>" 
              << " <TTPGA-config-file>" 
              << " <number-of-executions>"
              << " [<log-output-directory> [<standard-output-file>]]" << std::endl;
}

int main( int argc, char *argv[] )
{
    if( argc < 4 )
    {
        printHelp();
        return ErrorTypes::NUM_ARGS;
    }

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

    unsigned numExecs = 0;
    try
    {
        numExecs = std::stoi( argv[ 3 ] );
    }
    catch( std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        return ErrorTypes::EXCEPTION;
    }

    std::cout << "\n\n===============================" << std::endl
              << "-------- GA INITIATED ---------" << std::endl;

    TTPGA ga;
    std::vector< TTPIndividual > bestIndividuals;
    bestIndividuals.reserve( numExecs );

    for( unsigned i = 1; i <= numExecs; i++ )
    {
        std::cout << "\n===============================" << std::endl
                  << "----- EXECUTION " << i << " STARTED -----" << std::endl;

        std::cout << "Date and time: " << IndividualRecorder::getSuffixDateTime() << std::endl;

        try
        {
            TTPGAConfig gaC1 = TTPGAConfig::readTTPGAConfigFromFile( argv[ 2 ] );

            ga.gaConfig = gaC1;

            TTPInstance problem( argv[ 1 ] );

            std::cout << "Problem: " << problem.probFileName << std::endl;
            std::cout << "GA configurations: \n" << gaC1.toString() << std::endl;

            if( argc >= 5 )
            {
                ga.outputDirectory = argv[ 4 ];
            }

            ga.problem = problem;
            ga.run();

            TTPIndividual ind = ga.getBestNIndividuals( 1 )[ 0 ];
            bestIndividuals.push_back( ind );
            std::cout << "Best Individual: " << ind.toString() << std::endl;

            std::cout << "Total Execution Time: " << std::chrono::duration_cast< std::chrono::milliseconds >
                                                                               ( ga.executionTime ).count() 
                                                  << " milliseconds" << std::endl;
            std::cout << "Number of processed generations: " << ga.numProcGens << std::endl;
        }
        catch( std::exception& e )
        {
            std::cerr << e.what() << std::endl;
            return ErrorTypes::EXCEPTION;
        }

        std::cout << "-----  EXECUTION " << i << " DONE  ------" << std::endl
                  << "===============================" << std::endl;
    }

    std::vector< double > fitnessOfTheBests;
    fitnessOfTheBests.reserve( bestIndividuals.size() );
    for( TTPIndividual& ind : bestIndividuals )
    {
        fitnessOfTheBests.push_back( ind.fitness );
    }

    double sumFits = std::accumulate( std::begin( fitnessOfTheBests ), std::end( fitnessOfTheBests ), 0.0 );
    double meanFits = sumFits / fitnessOfTheBests.size();
    double accum = 0.0;
    std::for_each( std::begin( fitnessOfTheBests ), std::end( fitnessOfTheBests ), [ & ]( const double d ) 
                                                                                   {
                                                                                       accum += ( d - meanFits ) * ( d - meanFits );
                                                                                   });
    double stdevFits = std::sqrt( accum / ( fitnessOfTheBests.size() - 1 ) );
    
    std::cout << "\nFitness of the best individuals: " << std::endl;
    for( std::size_t i = 1; i <= bestIndividuals.size(); i++ )
    {
        std::cout << "    Execution " << i << ": " << bestIndividuals[ i - 1 ].fitness << std::endl;
    }

    std::cout << "\nFitness of the best individual of all executions: " << GeneticUtils::getBestNIndividuals( bestIndividuals, 1 )[ 0 ].fitness << std::endl;
    std::cout << "Fitness of the worst individual of all executions: " << GeneticUtils::getWorstNIndividuals( bestIndividuals, 1 )[ 0 ].fitness << std::endl;
    std::cout << "Average Fitness: " << meanFits << std::endl;
    std::cout << "Sample standard deviation: " << stdevFits << std::endl;

    std::cout << "\n----------  GA DONE  ----------" << std::endl
              << "===============================" << std::endl;

    std::cout.rdbuf( stcout );

    return 0;
}

