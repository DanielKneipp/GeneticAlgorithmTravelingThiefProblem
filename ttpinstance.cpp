#include "ttpinstance.hpp"

TTPInstance::TTPInstance( const std::string& fileName ) : isLoaded( false ),
                                                          numCities( 0 ),
                                                          numItems( 0 ),
                                                          knapCapacity( 0 ),
                                                          speedMax( 0.0 ),
                                                          speedMin( 0.0 )
{
    if( fileName != "" )
        this->readProblem( fileName );
}

void TTPInstance::readProblem( const std::string& fileName )
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
                this->rentingRate = std::stof( tmpString );
            }
            else if( tmpString == "Y):" ) // start enumerating all the cities
            {
                this->cities = std::vector< City >( this->numCities );
                for( unsigned long i = 0; i < this->numCities; i++ )
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
                this->items = std::vector< Item >( this->numItems );
                for( unsigned long i = 0; i < this->numItems; i++ )
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

    // Calculate the pwRatio.
    for( unsigned long i = 0; i < this->numCities; i++ )
    {
        try
        {
            this->cities[ i ].calcPwRatio();
        }
        catch( std::overflow_error& e )
        {
            std::cerr << e.what() << std::endl;
        }
    }

    // Calculate the number of items per city.
    // -1 to remove the first city (that don't have items).
    this->numItemsPerCity = this->numItems / ( this->numCities - 1 );
}

void TTPInstance::evaluateIndividual( TTPIndividual& individual )
{
    double fitness = 0.0;
    const double v = ( this->speedMax - this->speedMin ) / static_cast< double >( this->knapCapacity );

    unsigned long totalValue = 0;
    unsigned long totalWeight = 0;
    double totalPenalty = 0.0;

    // Get the total profit.
    for( unsigned long i = 0; i < this->numItems; i++ )
    {
        totalValue += this->items[ i ].profit * individual.features.pickingPlan[ i ];
    }

    // Get the penalty of the first city to the second that the totalWeight is 0.
    totalPenalty += this->cities[ 0 ].euclDistTo( this->cities[ 1 ] ) / ( this->speedMax );
    for( unsigned long i = 1; i < this->numCities - 1; i++ )
    {
        // Calculate the total weight of the picked items in the city i.
        for( unsigned long k = 0; k < this->numItemsPerCity; k++ )
        {
            // -1 because the first line of items references to city 2.
            const unsigned long itemPos = ( this->numItemsPerCity * ( i - 1 ) ) + k;
            totalWeight += this->items[ itemPos ].weight * individual.features.pickingPlan[ itemPos ];
        }

        totalPenalty += this->cities[ i ].euclDistTo( this->cities[ i + 1 ] ) /
                        ( this->speedMax - v * static_cast< double >( totalWeight ) );
    }
    // Calculate the total weight of the picked items in the last city.
    for( unsigned long k = 0; k < this->numItemsPerCity; k++ )
    {
        const unsigned long itemPos = ( this->numItemsPerCity * ( ( this->numCities - 1 ) - 1 ) ) + k;
        totalWeight += this->items[ itemPos ].weight * individual.features.pickingPlan[ itemPos ];
    }
    totalPenalty += this->cities[ this->numCities - 1 ].euclDistTo( this->cities[ 0 ] ) /
                    ( this->speedMax - v * static_cast< double >( totalWeight ) );

    fitness = totalValue - this->rentingRatio * totalPenalty;
    fitness += TTPInstance::penalizatioMethod( totalWeight );

    individual.fitness = fitness;
}

double TTPInstance::penalizationMethod( unsigned long totalWeight )
{
    double penalization = 0.0;

    penalization = 1000 * std::pow( std::max( totalWeight - this->knapCapacity, 0 ), 3 );

    return penalization;
}
