#include <iostream>
#include <vector>

#include "ttpga.hpp"
#include "ttpindividual.hpp"
#include "ttpinstance.hpp"

int main(int argc, char *argv[])
{
    TTPGA ga;

    try
    {
        TTPInstance problem( argv[ 1 ] );
        ga.problem = problem;
        ga.run( 120, 200 );

        std::cout << "Execution Time: " << ga.executionTime.count() << " seconds" << std::endl;

        std::vector< TTPIndividual > ind = ga.getBestNIndividuals( 1 );
        std::cout << "Best Individual: " << ind[ 0 ].toString() << std::endl;
    }
    catch( std::exception& e )
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}

