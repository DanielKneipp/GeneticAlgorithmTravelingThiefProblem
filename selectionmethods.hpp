#ifndef SELECTIONMETHODS
#define SELECTIONMETHODS

#include <vector>
#include <algorithm>

#include "geneticutils.hpp"

#include "selectionmethods.cpp"

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
std::vector< T > tournament( const unsigned long tournamentSize,
                             const unsigned long newPopulationSize,
                             const std::vector< T >& population );
/**
 * @brief fightClub             Uses the \ref tournament method to select
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
std::vector< T > fightClub( const unsigned long tournamentSize,
                            const unsigned long newPopulationSize,
                            const unsigned long numElites,
                            const std::vector< T >& population );

}


#endif // SELECTIONMETHODS

