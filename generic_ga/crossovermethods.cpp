#include "crossovermethods.hpp"

namespace CrossoverMethod
{

template< typename T_f, typename T_idx >
std::array< std::vector< T_f >, 2 > alternateNCutPoints( const std::vector< T_f >& featuresParent1,
                                                         const std::vector< T_f >& featuresParent2,
                                                         const std::vector< T_idx >& cutPoints)
{
    std::array< std::vector< T_f >, 2 > children;

    const std::size_t featureVectorSize = featuresParent1.size(); // or featuresParent2.size()
    children[ 0 ].reserve( featureVectorSize );
    children[ 1 ].reserve( featureVectorSize );

    const float p = GeneticUtils::genRealRandNumber< float >( 0.f, 1.f );
    if( p > 0.5 ) // If it will starts with Parent1 -> Offspring1 and Parent2 -> Offspring2
    {
        for( std::size_t i = 0, j = 0; i < featureVectorSize; i++ )
        {
            if( i == cutPoints[ j ] )
            {
                j++;
            }

            if( j % 2 == 0 )
            {
                children[ 0 ].push_back( featuresParent1[ i ] );
                children[ 1 ].push_back( featuresParent2[ i ] );
            }
            else
            {
                children[ 1 ].push_back( featuresParent1[ i ] );
                children[ 0 ].push_back( featuresParent2[ i ] );
            }
        }
    }
    else
    {
        for( std::size_t i = 0, j = 0; i < featureVectorSize; i++ )
        {
            if( i == cutPoints[ j ] )
            {
                j++;
            }

            if( j % 2 != 0 )
            {
                children[ 0 ].push_back( featuresParent1[ i ] );
                children[ 1 ].push_back( featuresParent2[ i ] );
            }
            else
            {
                children[ 1 ].push_back( featuresParent1[ i ] );
                children[ 0 ].push_back( featuresParent2[ i ] );
            }
        }
    }

    return children;
}

template< typename T_f >
std::array< std::vector< T_f >, 2 > orderBased( const std::vector< T_f >& featuresParent1,
                                                const std::vector< T_f >& featuresParent2 )
{
    const std::size_t featureVectorSize = featuresParent1.size(); // or featuresParent2.size()
    std::array< std::vector< T_f >, 2 > children = { std::vector< T_f >( featureVectorSize ),
                                                     std::vector< T_f >( featureVectorSize ) };
    std::vector< unsigned short > mask( featureVectorSize );

    // Generating mask
    for( unsigned short& i : mask )
    {
        i = GeneticUtils::genIntRandNumber< unsigned short >( 0, 1 );
    }

    for( std::size_t i = 0; i < featureVectorSize; i++ )
    {
        if( mask[ i ] )
        {
            children[ 0 ][ i ] = featuresParent1[ i ];
            children[ 1 ][ i ] = featuresParent2[ i ];
        }
    }

    std::vector< GeneticUtils::valueWithIdx< T_f > > fp1WithIndexes;
    std::vector< GeneticUtils::valueWithIdx< T_f > > fp2WithIndexes;

    fp1WithIndexes.reserve( featureVectorSize );
    fp2WithIndexes.reserve( featureVectorSize );

    for( std::size_t i = 0; i < featureVectorSize; i++ )
    {
        if( !mask[ i ] )
        {
            GeneticUtils::valueWithIdx< T_f > viP1;
            viP1.value = featuresParent1[ i ];
            viP1.index = std::find( featuresParent2.begin(),
                                    featuresParent2.end(),
                                    featuresParent1[ i ] ) - featuresParent2.begin();
            fp1WithIndexes.push_back( viP1 );

            GeneticUtils::valueWithIdx< T_f > viP2;
            viP2.value = featuresParent2[ i ];
            viP2.index = std::find( featuresParent1.begin(),
                                    featuresParent1.end(),
                                    featuresParent2[ i ] ) - featuresParent1.begin();
            fp2WithIndexes.push_back( viP2 );
        }
    }

    std::sort( fp1WithIndexes.begin(), fp1WithIndexes.end() );
    std::sort( fp2WithIndexes.begin(), fp2WithIndexes.end() );

    for( std::size_t i = 0, j = 0; i < featureVectorSize; i++ )
    {
        if( !mask[ i ] )
        {
            children[ 0 ][ i ] = fp1WithIndexes[ j ].value;
            children[ 1 ][ i ] = fp2WithIndexes[ j ].value;
            j++;
        }
    }

    return children;
}

}
