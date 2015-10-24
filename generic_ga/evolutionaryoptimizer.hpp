#ifndef EVOLUTIONARYOPTIMIZER_HPP
#define EVOLUTIONARYOPTIMIZER_HPP

#include <vector>
#include <chrono>
#include <algorithm>

#include "problem.hpp"

#include "../utils/geneticutils.hpp"

template< class T_ind, class T_prob >
class EvolutionaryOptimizer
{
protected:
    /** Individuals */
    std::vector< T_ind > population;
    /** Moment of the time that \ref startTimer() was executed. */
    std::chrono::steady_clock::time_point startTime;
    /** Moment of the time that \ref stopTimer() was executed. */
    std::chrono::steady_clock::time_point stopTime;

    /**
     * @brief startTimer                Start the timer.
     */
    void startTimer();
    /**
     * @brief stopTimer                 Stop the timer and get the difference between
     *                                  the moment of the time that startTimer was
     *                                  executed and the present moment and store that
     *                                  in \ref executionTime variable.
     */
    void stopTimer();
    /**
     * @brief generatePopulation    Generate the population. Commonly used to
     *                              create the initial population.
     *
     * @param numIndividuals        Number of individuals that will be generated.
     *
     * @return                      The generated individuals.
     */
    virtual std::vector< T_ind > generatePopulation( unsigned numIndividuals ) = 0;


public:
    /** Execution Time in microseconds. \ref startTime() and \ref stopTime()
      * must to be used at this order to \ref executionTime has a value assigned. */
    std::chrono::microseconds executionTime;
    /** Problem to be solved. */
    T_prob problem;

    /**
     * @brief EvolutionaryOptimizer     Constructor.
     */
    EvolutionaryOptimizer();
    /**
     * @brief ~EvolutionaryOptimizer    Destructor.
     */
    virtual ~EvolutionaryOptimizer();
    /**
     * @brief run                       Execute the evolutionary solver method.
     */
    virtual void run( unsigned numIndividuals,
                      unsigned numGenerations = 0 ) = 0;
    /**
     * @brief getBestNIndividuals       Used to get the best individuals in the
     *                                  population.
     *
     * @param numIndividuals            Number of individuals that will be returned.
     *
     * @return                          The best individuals in the population.
     */
    virtual std::vector< T_ind > getBestNIndividuals( unsigned numIndividuals );
};


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

    this->executionTime = std::chrono::duration_cast< std::chrono::microseconds >
                                                    ( this->stopTime - this->startTime );
}

template< class T_ind, class T_prob >
std::vector< T_ind > EvolutionaryOptimizer< T_ind, T_prob >::getBestNIndividuals( unsigned numIndividuals )
{
    return GeneticUtils::getBestNIndividuals( this->population, numIndividuals );
}


#endif // EVOLUTIONARYOPTIMIZER_HPP
