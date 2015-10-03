#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <string>
#include <vector>

template< class T >
class Problem
{
public:
    /** Specify if the problem is already loaded from a file. */
    bool isLoaded;

    /**
     * @brief Problem           Constructor.
     */
    Problem();
    /**
     * @brief ~Problem          Destructor.
     */
    virtual ~Problem();
    /**
     * @brief   readProblem     Load a Problem from file.
     *
     * @param   fileName        File that specify the Problem.
     */
    virtual void readProblem( const std::string& fileName ) = 0;
    /**
     * @brief evaluateIndividual    Evaluate the individual and set
     *                              his fitness (the individual must have
     *                              a \c public \c float variable with the name \c fitness).
     *
     * @param Individual            Individual that will be evaluated.
     */
    virtual void evaluateIndividual( T& individual ) = 0;
    /**
     * @brief evaluateIndividuals   Evaluate a lot of individuals using
     *                              {@ref evaluateIndividual( T& )} method.
     *
     * @param population            Array of individuals.
     */
    virtual void evaluateIndividuals( std::vector< T >& population );
};

#include "problem.cpp"

#endif // PROBLEM_HPP
