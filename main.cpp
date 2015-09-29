#include <iostream>

#include "ttpga.hpp"
#include "ttpinstance.hpp"

int main(int argc, char *argv[])
{
    TTPGA ga;

    try
    {
        TTPInstance problem( argv[ 1 ] );
        ga.problem = problem;
        ga.run( 4, 100 );
    }
    catch( std::exception& e )
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Execution Time: " << ga.executionTime.count() << " seconds" << std::endl;

    return 0;
}

