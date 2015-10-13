#include "evolutionaryoptimizer.hpp"

template< class T_ind, class T_prob >
EvolutionaryOptimizer< T_ind, T_prob >::EvolutionaryOptimizer() {}

template< class T_ind, class T_prob >
EvolutionaryOptimizer< T_ind, T_prob >::~EvolutionaryOptimizer() {}

template< class T_ind, class T_prob >
void EvolutionaryOptimizer< T_ind, T_prob >::startTimer()
{
    this->startTime = std::chrono::steady_clock::now();
}

template< class T_ind, class T_prob >
void EvolutionaryOptimizer< T_ind, T_prob >::stopTimer()
{
    this->stopTime = std::chrono::steady_clock::now();

    this->executionTime = this->stopTime - this->startTime;
}

template< class T_ind, class T_prob >
std::vector< T_ind > EvolutionaryOptimizer< T_ind, T_prob >::getBestNIndividuals( unsigned numIndividuals )
{
    return GeneticUtils::getBestNIndividuals( this->population, numIndividuals );
}
