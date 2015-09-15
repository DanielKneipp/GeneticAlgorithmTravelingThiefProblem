#include "problem.hpp"

Problem::Problem()
{

}

template< typename T >
void Problem::evaluateIndividuals( std::vector< T >& population )
{
    for( T& individual : population )
    {
        this->evaluateIndividual( individual );
    }
}

