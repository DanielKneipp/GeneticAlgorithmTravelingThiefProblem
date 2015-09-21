#include "individual.hpp"

Individual::Individual() : fitness( 0.0 )
{

}

template< class T >
bool Individual::operator < ( const Individual< T >& i )
{
    return this->fitness < i.fitness;
}

template< class T >
bool Individual::operator <= ( const Individual< T >& i )
{
    return this->fitness <= i.fitness;
}

template< class T >
bool Individual::operator > ( const Individual< T >& i )
{
    return this->fitness > i.fitness;
}

template< class T >
bool Individual::operator >= ( const Individual< T >& i )
{
    return this->fitness >= i.fitness;
}
