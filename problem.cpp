#include "problem.hpp"

template< class T >
Problem< T >::Problem() : isLoaded( false ) {}

template< class T >
Problem< T >::~Problem() {}

template< class T >
void Problem< T >::evaluateIndividuals( std::vector< T >& population )
{
    for( T& individual : population )
    {
        this->evaluateIndividual( individual );
    }
}

