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
    std::vector< T_ind > partialSortedPopulation = this->population;
    std::partial_sort( partialSortedPopulation.begin(),
                       partialSortedPopulation.begin() + numIndividuals,
                       partialSortedPopulation.end(),
                       []( const T_ind& a, const T_ind& b ) -> bool
                       {
                           return a.fitness > b.fitness;
                       });
    return std::vector< T_ind >( partialSortedPopulation.begin(),
                                 partialSortedPopulation.begin() + numIndividuals );
}
