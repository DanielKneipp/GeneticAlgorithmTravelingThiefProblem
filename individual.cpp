#include "individual.hpp"

Individual::Individual() : fitness( 0.0 )
{

}

template< typename T >
bool Individual::operator < ( const Individual< T > &i )
{
    return this->fitness < i.fitness;
}

template< typename T >
bool Individual::operator <= ( const Individual< T > &i )
{
    return this->fitness <= i.fitness;
}

template< typename T >
bool Individual::operator > ( const Individual< T > &i )
{
    return this->fitness > i.fitness;
}

template< typename T >
bool Individual::operator >= ( const Individual< T > &i )
{
    return this->fitness >= i.fitness;
}
