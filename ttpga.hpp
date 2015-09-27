#ifndef TTPGA_HPP
#define TTPGA_HPP

#include <vector>
#include <algorithm>
#include <exception>

#include "evolutionaryoptimizer.hpp"
#include "individual.hpp"
#include "ttpinstance.hpp"
#include "ttpmutationmethods.hpp"
#include "selectionmethods.hpp"

class TTPGA : EvolutionaryOptimizer< TTPIndividual, TTPInstance >
{
public:
    /**
     * @brief TTPGA     Constructor.
     */
    TTPGA();
};

#endif // TTPGA_HPP
