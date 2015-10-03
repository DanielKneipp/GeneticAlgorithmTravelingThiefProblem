#include "ttpinstance.hpp"

TTPInstance::TTPInstance( const std::string& fileName ) : numCities( 0 ),
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
                    this->cities[ i ].index = i + 1;
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
                    this->items[ i ].cityIndex = std::stoul( tmpString );
                    this->cities[ this->items[ i ].cityIndex - 1 ].totalProfit += this->items[ i ].profit;
                    this->cities[ this->items[ i ].cityIndex - 1 ].totalWeight += this->items[ i ].weight;
                }
                break; // break the while loop -> file parsing done.
            }
        } // end_while

        this->isLoaded = true;
        file.close();
    }

    // Calculate the pwRatio.
    for( unsigned long i = 1; i < this->numCities; i++ )
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
    // -1 because index of the city i is i but his position in the vector of cities is i-1 (starts with 0 instead of 1).
    totalPenalty += this->cities[ individual.features.tour[ 0 ] - 1 ].euclDistTo( this->cities[ individual.features.tour[ 1 ] - 1 ] ) / ( this->speedMax );
    for( unsigned long i = 1; i < this->numCities; i++ )
    {
        // Calculate the total weight of the picked items in the city i.
        for( unsigned long k = 0; k < this->numItemsPerCity; k++ )
        {
            // -1 because the first line of items references to city 2.
            const unsigned long itemPos = ( this->numItemsPerCity * ( individual.features.tour[ i ] - 1 - 1 ) ) + k;
            totalWeight += this->items[ itemPos ].weight * individual.features.pickingPlan[ itemPos ];
        }

        totalPenalty += this->cities[ individual.features.tour[ i ] - 1 ].euclDistTo( this->cities[ individual.features.tour[ i + 1 ] - 1 ] ) /
                        ( this->speedMax - v * static_cast< double >( totalWeight ) );
    }

    // Note: The calculations assume that the total weight of picked items wont exceed
    // the knapsack capacity, so if it happen the calculations should be disconsidered
    // and a pure penalization be applied instead.
    if( totalWeight > this->knapCapacity )
    {
        fitness = TTPInstance::penalizationMethod( totalWeight );
    }
    else
    {
        fitness = totalValue - this->rentingRate * totalPenalty;
    }

    individual.fitness = fitness;
}

double TTPInstance::penalizationMethod( unsigned long totalWeight )
{
    double penalization = 0.0;

    penalization = - ( 10000 + std::pow( std::max( totalWeight - this->knapCapacity,
                                                   ( unsigned long )( 0 ) ), 3 ) );

    return penalization;
}
