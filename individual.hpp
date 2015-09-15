#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <vector>
#include <string>

#include "individual.cpp"

template< typename T >
class Individual
{
public:

    T features;

    float fitness;


    Individual();

    bool operator < ( const Individual< T >& i );

    bool operator <= ( const Individual< T >& i );

    bool operator >= ( const Individual< T >& i );

    bool operator > ( const Individual< T >& i );

    virtual std::string toString() = 0;
};

#endif // INDIVIDUAL_HPP
