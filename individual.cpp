#include "individual.hpp"

template< class T >
Individual< T >::Individual() : fitness( 0.0 ) {}

template< class T >
Individual< T >::~Individual() {}

template< class T >
bool Individual< T >::operator < ( const Individual< T >& i ) const
{
    return this->fitness < i.fitness;
}

template< class T >
bool Individual< T >::operator <= ( const Individual< T >& i ) const
{
    return this->fitness <= i.fitness;
}

template< class T >
bool Individual< T >::operator > ( const Individual< T >& i ) const
{
    return this->fitness > i.fitness;
}

template< class T >
bool Individual< T >::operator >= ( const Individual< T >& i ) const
{
    return this->fitness >= i.fitness;
}
