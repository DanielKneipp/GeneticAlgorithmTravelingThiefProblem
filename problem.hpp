#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <string>
#include <vector>

#include "problem.cpp"

template< typename T >
class Problem
{
public:
    /** Specify if the problem is already loaded from a file. */
    bool isLoaded;


    Problem();
    /**
     * @brief   readProblem     Load a Problem from file.
     *
     * @param   fileName        File that specify the Problem.
     */
    virtual void readProblem( std::string& fileName ) = 0;

    virtual void evaluateIndividual( T& Individual ) = 0;

    virtual void evaluateIndividuals( std::vector< T >& population );

};

#endif // PROBLEM_HPP
