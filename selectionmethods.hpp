#ifndef SELECTIONMETHODS
#define SELECTIONMETHODS

#include <vector>

#include "selectionmethods.cpp"

namespace SelectionMethod
{

template< typename T >
void tournament( unsigned short size,
                 std::vector< T >& population );

template< typename T >
void fightClub( unsigned short size,
                std::vector< T >& population );
}


#endif // SELECTIONMETHODS

