#include "city.hpp"

City::City() : index( 0 ),
               xCord( 0 ),
               yCord( 0 ),
               totalProfit( 0 ),
               totalWeight( 0 ),
               wpRatio( 0.0 )
{}

float City::euclDistTo( const City& dst )
{
    double diffX = std::pow( static_cast< double >( this->xCord - dst.xCord ), 2 );
    double diffY = std::pow( static_cast< double >( this->yCord - dst.yCord ), 2 );

    return static_cast< float >( std::sqrt( diffX + diffY ) );
}

void City::calcPwRatio()
{
    if( this->totalWeight != 0 )
    {
        this->pwRatio = static_cast< float >(
                        static_cast< double >( this->totalProfit ) /
                        static_cast< double >( this->totalWeight ) );
    }
    else
    {
        throw std::overflow_error( "Total weight in the city " +
                                   std::to_string( this->index ) + " is equal to 0" );
    }
}
