#include "item.hpp"

Item::Item() : index( 0 ),
               profit( 0 ),
               weight( 0 ),
               cityIndex( 0 ),
               pwRatio( 0 )
{}

void Item::calcPwRatio()
{
    if( this->weight != 0 )
    {
        this->pwRatio = static_cast< float >(
                        static_cast< double >( this->profit ) /
                        static_cast< double >( this->weight ) );
    }
    else
    {
        throw std::overflow_error( "Total weight of the item " +
                                   std::to_string( this->index ) + " is equal to 0" );
    }
}
