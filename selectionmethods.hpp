#ifndef SELECTIONMETHODS
#define SELECTIONMETHODS

#include <vector>

#include "selectionmethods.cpp"

namespace SelectionMethod
{

template< class T >
void tournament( unsigned short size,
                 std::vector< T >& population );

template< class T >
void fightClub( unsigned short size,
                std::vector< T >& population );
}


#endif // SELECTIONMETHODS

