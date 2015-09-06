#include "ttpinstance.hpp"

TTPInstance::TTPInstance( std::string fileName ) : isLoaded( false ),
                                                   numCities( 0 ),
                                                   numItems( 0 ),
                                                   knapCapacity( 0 ),
                                                   speedMax( 0.0 ),
                                                   speedMin( 0.0 )
{
    if( fileName != "" )
        this->readProblem( fileName );
}

void TTPInstance::readProblem( std::string fileName )
{
    std::ifstream file( fileName );
    if( file.is_open() )
    {
        std::string tmpString;
        while( true )
        {
            file >> tmpString;
            if( tmpString == "DIMENSION:" )
            {
                file >> tmpString;
                this->numCities = std::stoul( tmpString );
            }
            else if( tmpString == "ITEMS:" )
            {
                file >> tmpString;
                this->numItems = std::stoul( tmpString );
            }
            else if( tmpString == "KNAPSACK:" )
            {
                file >> tmpString;
                this->knapCapacity = std::stoul( tmpString );
            }
            else if( tmpString == "MIN" )
            {
                file >> tmpString;
                file >> tmpString;
                this->speedMin = std::stof( tmpString );
            }
            else if( tmpString == "MAX" )
            {
                file >> tmpString;
                file >> tmpString;
                this->speedMax = std::stof( tmpString );
            }
            else if( tmpString == "RATIO:" )
            {
                file >> tmpString;
                this->rentingRatio = std::stof( tmpString );
            }
            else if( tmpString == "Y):" ) // start enumerating all the cities
            {
                this->cities = std::unique_ptr< City[] >( new City[ this->numCities + 1 ] ); // skip 0
                for( unsigned long i = 1; i != this->numCities + 1; i++ )
                {
                    this->cities[ i ].index = i;
                    file >> tmpString; // index
                    file >> tmpString;
                    this->cities[ i ].xCord = std::stoul( tmpString );
                    file >> tmpString;
                    this->cities[ i ].yCord = std::stoul( tmpString );
                    this->cities[ i ].totalProfit = 0;
                    this->cities[ i ].totalWeight = 0;
                }
            }
            else if( tmpString == "NUMBER):" ) // start enumerating all the items
            {
                this->items = std::unique_ptr< Item[] >( new Item[ this->numItems + 1 ] ); // skip 0
                for( unsigned long i = 1; i != this->numItems + 1; i++ )
                {
                    file >> tmpString; // index
                    file >> tmpString;
                    this->items[ i ].profit = std::stoul( tmpString );
                    file >> tmpString;
                    this->items[ i ].weight = std::stoul( tmpString );
                    file >> tmpString;
                    this->items[ i ].inCity = std::stoul( tmpString );
                    this->cities[ this->items[ i ].inCity ].totalProfit += this->items[ i ].profit;
                    this->cities[ this->items[ i ].inCity ].totalWeight += this->items[ i ].weight;
                }
                break; // break the while loop -> file parsing done.
            }
        } // end_while
        this->isLoaded = true;
        file.close();
    }
    // Calcule the pwRatio
    for( unsigned long i = 1; i <= this->numCities; i++ )
    {
        this->cities[ i ].pwRatio = static_cast< float >(
                                    static_cast< double >( thisProb->cities[ i ].totalProfit ) /
                                    static_cast< double >( thisProb->cities[ i ].totalWeight ) );
    }
}
