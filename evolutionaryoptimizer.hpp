#ifndef EVOLUTIONARYOPTIMIZER_HPP
#define EVOLUTIONARYOPTIMIZER_HPP

#include <vector>

#include "problem.hpp"

#include "evolutionaryoptimizer.cpp"

template< typename T_ind, typename T_prob >
class EvolutionaryOptimizer
{
private:

    std::vector< T_ind > individuals;


    virtual std::vector< T_ind > generatePopulation( numIndividuals ) = 0;


public:

    double executionTime;

    T_prob problem;


    EvolutionaryOptimizer();

    void startTimer();

    void stopTimer();

    virtual void run() = 0;
};

#endif // EVOLUTIONARYOPTIMIZER_HPP
