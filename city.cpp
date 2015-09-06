#include "city.hpp"

City::City() : index( 0 ),
               xCord( 0 ),
               yCord( 0 ),
               totalProfit( 0 ),
               totalWeight( 0 ),
               wpRatio( 0.0 )
{}

float City::euclDistTo( City& dst )
{
    double diffX = std::pow( static_cast< double >( this->xCord - dst.xCord ), 2 );
    double diffY = std::pow( static_cast< double >( this->yCord - dst.yCord ), 2 );

    return static_cast< float >( std::sqrt( diffX + diffY ) );
}
