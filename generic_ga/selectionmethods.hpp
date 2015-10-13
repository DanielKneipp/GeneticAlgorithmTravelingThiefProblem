#ifndef SELECTIONMETHODS
#define SELECTIONMETHODS

#include <vector>
#include <algorithm>

#include "../utils/geneticutils.hpp"

namespace SelectionMethod
{

/**
 * @brief tournament            Tournament method. Selects the best individual
 *                              by each tournament of a specific size. The number
 *                              of the tournaments specifies the size of the selected
 *                              population.
 *
 * @param tournamentSize        Size of the tournament.
 *
 * @param newPopulationSize     Size of the selected population.
 *
 * @param population            Population to be selected.
 *
 * @return                      The selected population.
 */
template< class T >
std::vector< T > tournament( const std::vector< T >& population,
                             const unsigned long tournamentSize,
                             const unsigned long newPopulationSize );

/**
 * @brief tournament_elitism    Uses the \ref tournament method to select
 *                              (\ref newPopulationSize - \ref numElites) solutions but
 *                              ensure that \ref numElites best solutions will be kept to
 *                              selected population group.
 *
 * @param tournamentSize        Size of the tournament.
 *
 * @param newPopulationSize     Size of the selected population.
 *
 * @param numElites             Number of elite solutions to be kept.
 *
 * @param population            Population to be selected.
 *
 * @return                      The selected population.
 */
template< class T >
std::vector< T > tournament_elitism( const std::vector< T >& population,
                                     const unsigned long tournamentSize,
                                     const unsigned long newPopulationSize,
                                     const unsigned long numElites );

}

#include "selectionmethods.cpp"

#endif // SELECTIONMETHODS
