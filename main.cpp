#include <iostream>

#include "ttpga.hpp"

using namespace std;

int main()
{
    TTPGA ga;

    ga.startTimer();
    try
    {
        ga.run( 4, 100 );
    }
    catch( std::exception& e )
    {
        std::cout << e.what() << std::endl;
    }
    ga.stopTimer();

    std::cout << "Execution Time: " << ga.executionTime.count() << " seconds" << std::endl;

    return 0;
}

