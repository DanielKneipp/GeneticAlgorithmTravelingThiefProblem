#include "problem.hpp"

Problem::Problem()
{

}

template< class T >
void Problem::evaluateIndividuals( std::vector< T >& population )
{
    for( T& individual : population )
    {
        this->evaluateIndividual( individual );
    }
}

