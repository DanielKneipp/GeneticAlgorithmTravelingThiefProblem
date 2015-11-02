#include "ttpga.hpp"

TTPGA::TTPGA() : outputDirectory( "" ),
                 numProcGens( 0 )
{}

void TTPGA::run()
{
    if( this->gaConfig.NUM_INDIVIDUALS % 2 != 0 )
    {
        throw std::invalid_argument( "numIndividuals must to be an even number" );
    }
    if( !this->problem.isLoaded )
    {
        throw std::logic_error( "Problem is not loaded yet!" );
    }

    unsigned countGens = 0;
    this->numProcGens = 0;

    unsigned countGensWithoutImprov = 0;
    std::chrono::milliseconds milliExecTime = std::chrono::milliseconds( 0 );

#if defined( __GA_PLOT_ ) || defined( __GA_LOG_ )
    std::string stringSpecs = std::string( "i=" ) + std::to_string( this->gaConfig.NUM_INDIVIDUALS ) +
                              "-ng="    + std::to_string( this->gaConfig.MAX_GENS_WITHOUT_IMPROV ) +
                              "-t="     + std::to_string( this->gaConfig.MAX_EXEC_TIME.count() ) +
                              "-ts_s="  + std::to_string( this->gaConfig.TOURNAMET_SIZE ) +
                              "-ts_c="  + std::to_string( this->gaConfig.TOURNAMET_SIZE_CROSSOVER ) +
                              "-ne_s="  + std::to_string( this->gaConfig.SELECTION_NUM_ELITES ) +
                              "-sne_c=" + std::to_string( this->gaConfig.SELECTION_NUM_ELITES_CROSSOVER ) +
                              "-ne_m="  + std::to_string( this->gaConfig.MUTATION_NUM_ELITES ) +
                              "-nc_c="  + std::to_string( this->gaConfig.NUM_CUT_POINTS ) +
                              "-a_m="   + std::to_string( this->gaConfig.ALPHA_PROBABILITY );

    IndividualRecorder rec;
#endif // __GA_PLOT_ || __GA_LOG_
#ifdef __GA_PLOT_
    rec.setDestinationFileFit( this->outputDirectory + 
                               this->problem.probFileName +
                               "__" + IndividualRecorder::getSuffixDateTime() + 
                               "__" + stringSpecs + ".dat" );
#endif //__GA_PLOT_
#ifdef __GA_LOG_
    rec.setDestinationFileLog( this->outputDirectory + 
                               this->problem.probFileName +
                               "__" + IndividualRecorder::getSuffixDateTime() + 
                               "__" + stringSpecs + ".log" );
    rec.prepareFileLog();
    rec.writeInLogFile( "NUM_INDIVIDUALS", std::to_string( this->gaConfig.NUM_INDIVIDUALS ) );
    rec.writeInLogFile( "MAX_GENS_WITHOUT_IMPROV", std::to_string( this->gaConfig.MAX_GENS_WITHOUT_IMPROV ) );
    rec.writeInLogFile( "MAX_EXEC_TIME", std::to_string( this->gaConfig.MAX_EXEC_TIME.count() ) );
    rec.writeInLogFile( "TOURNAMET_SIZE", std::to_string( this->gaConfig.TOURNAMET_SIZE ) );
    rec.writeInLogFile( "TOURNAMET_SIZE_CROSSOVER", std::to_string( this->gaConfig.TOURNAMET_SIZE_CROSSOVER ) );
    rec.writeInLogFile( "SELECTION_NUM_ELITES", std::to_string( this->gaConfig.SELECTION_NUM_ELITES ) );
    rec.writeInLogFile( "SELECTION_NUM_ELITES_CROSSOVER", std::to_string( this->gaConfig.SELECTION_NUM_ELITES_CROSSOVER ) );
    rec.writeInLogFile( "MUTATION_NUM_ELITES", std::to_string( this->gaConfig.MUTATION_NUM_ELITES ) );
    rec.writeInLogFile( "NUM_CUT_POINTS", std::to_string( this->gaConfig.NUM_CUT_POINTS ) );
    rec.writeInLogFile( "ALPHA_PROBABILITY", std::to_string( this->gaConfig.ALPHA_PROBABILITY ) );
    rec.writeInLogFile( "CONFIG_NAME", this->gaConfig.CONFIG_NAME );
    rec.writeInLogFile(  "\"individuals\" : {\n\n" );
#endif // __GA_LOG_

    // std::function< std::vector< TTPIndividual >( const std::vector< TTPIndividual >& ) > 
    auto mutFunc = std::bind( TTPMutationMethod::twoOpt_bitFlip_likely, 
                              std::placeholders::_1, 
                              this->gaConfig.ALPHA_PROBABILITY );
    // std::function< std::vector< TTPIndividual >( const std::vector< TTPIndividual >&, std::size_t ) >
    auto selFunc = std::bind( SelectionMethod::tournament< TTPIndividual >, 
                              std::placeholders::_1, 
                              this->gaConfig.TOURNAMET_SIZE,
                              std::placeholders::_2 );
    // std::function< std::vector< TTPIndividual >( const std::vector< TTPIndividual >&, std::size_t ) >
    auto selFunc_cross = std::bind( SelectionMethod::tournament< TTPIndividual >, 
                                    std::placeholders::_1, 
                                    this->gaConfig.TOURNAMET_SIZE_CROSSOVER,
                                    std::placeholders::_2 );

    this->startTimer();

    this->population = this->generatePopulation( this->gaConfig.NUM_INDIVIDUALS );
    this->problem.evaluateIndividuals( this->population );

    TTPIndividual bestIndCurr;
    if( this->gaConfig.MAX_GENS_WITHOUT_IMPROV != 0 )
    {
        bestIndCurr = this->getBestNIndividuals( 1 )[ 0 ];
    }
    

    while( ( this->gaConfig.MAX_GENS_WITHOUT_IMPROV == 0 ||
             countGensWithoutImprov < this->gaConfig.MAX_GENS_WITHOUT_IMPROV ) &&
           ( this->gaConfig.MAX_EXEC_TIME.count() == 0 || 
             milliExecTime.count() < this->gaConfig.MAX_EXEC_TIME.count() ) )
    {
        //** Selection Step **//
        this->population = SelectionMethod::generic_elitism( this->population,
                                                             this->gaConfig.SELECTION_NUM_ELITES_CROSSOVER,
                                                             this->gaConfig.NUM_INDIVIDUALS ,
                                                             selFunc );

        //** Crossover Step **//
        std::vector< TTPIndividual > children = TTPCrossoverMethod::orderBased_alternate( this->population,
                                                                                          this->gaConfig.NUM_CUT_POINTS );
        this->problem.evaluateIndividuals( children );
        this->population.insert( this->population.end(), children.begin(), children.end() );
        this->population = SelectionMethod::generic_elitism( this->population,
                                                             this->gaConfig.SELECTION_NUM_ELITES_CROSSOVER,
                                                             this->gaConfig.NUM_INDIVIDUALS ,
                                                             selFunc_cross );

        //** Mutation Step **//
        this->population = MutationMethods::generic_elitism( this->population, 
                                                             this->gaConfig.MUTATION_NUM_ELITES,
                                                             mutFunc );

        //** Evaluation Step **//
        this->problem.evaluateIndividuals( this->population );


        milliExecTime = std::chrono::duration_cast< std::chrono::milliseconds >
                                                  ( std::chrono::steady_clock::now() - this->startTime );


        TTPIndividual bestIndGen = this->getBestNIndividuals( 1 )[ 0 ];

        if( this->gaConfig.MAX_GENS_WITHOUT_IMPROV != 0 )
        {
            if( bestIndGen.fitness <= bestIndCurr.fitness )
            {
                countGensWithoutImprov++;
            }
            else
            {
                countGensWithoutImprov = 0;
                bestIndCurr = bestIndGen;
            }
        }

#ifdef __GA_DETAILED_COUT_
        std::cout << "Generation " << countGens + 1 << " processed." << std::endl;
        std::cout << "Fitness of the best individual: " << bestIndGen.fitness << std::endl;
        std::cout << "Execution time: " << milliExecTime.count() << " milliseconds" << std::endl;
#endif // __GA_DETAILED_COUT_
#ifdef __GA_PLOT_
        rec.recordIndFitnessToFileFit( bestIndGen );
#endif // __GA_PLOT_
#ifdef __GA_LOG_
        rec.recordIndFitnessToFileLog( bestIndGen );
#endif // __GA_LOG_

        countGens++;
    }

    this->stopTimer();

    this->numProcGens = countGens;

#ifdef __GA_LOG_
    rec.writeInLogFile( "}");
    rec.closeFileLog();
#endif // __GA_LOG_
#ifdef __GA_PLOT_
    rec.plot( "plotGAData.gp", this->gaConfig.CONFIG_NAME );
#endif // __GA_PLOT_
}

std::vector< TTPIndividual > TTPGA::generatePopulation( unsigned numIndividuals )
{
    std::vector< TTPIndividual > population;
    population.reserve( numIndividuals );
    std::string lkOutName = std::string( "lk_") + this->problem.probFileName + ".tour.temp";

    for( unsigned i = 0; i < numIndividuals; i++ )
    {
        TTPIndividual individual;


        //** Generating TSP component **//
        individual.features.tour = this->getLinkernTour( lkOutName, true );


        //** Generating KP component **//
        individual.features.pickingPlan = std::vector< unsigned short >( this->problem.numItems, 0 );


        population.push_back( individual );
    }

    return population;
}

std::vector< unsigned long > TTPGA::getLinkernTour( std::string lkOutFileNamePath, bool delFile )
{
    std::string command;
    std::vector< unsigned long > tour;

    tour.reserve( this->problem.numCities + 1 );

#ifdef _MSC_VER
    command = "linkern.exe";
#else
    command = "./linkern";
#endif // _MSC_VER
    command += std::string( " -o " ) + lkOutFileNamePath + " ";
    command += this->problem.probFileNamePath;

    std::system( command.c_str() );

    std::ifstream lkOutFile( lkOutFileNamePath );
    std::string tmpStirng;
    if( lkOutFile )
    {
        // Discard the first line.
        std::getline( lkOutFile, tmpStirng );
        for( std::size_t i = 0; i < this->problem.numCities; i++ )
        {
            std::getline( lkOutFile, tmpStirng );
            std::size_t p = tmpStirng.find_first_of( " " );
            tour.push_back( std::stoul( tmpStirng.substr( 0, p ) ) + 1 );  // + 1 because linkern writes the cities with
                                                                           // indexes starting from 0.
        }
        tour.push_back( 1 );
    }
    else
    {
        throw std::invalid_argument( std::string( "Cannot read the linkern output file " ) + lkOutFileNamePath );
    }

    lkOutFile.close();
    if( delFile )
    {
        std::remove( lkOutFileNamePath.c_str() );
    }
    
    return tour;
}

std::vector< unsigned long > TTPGA::genRandTSPComponent()
{
    std::vector< unsigned long > baseTour( this->problem.numCities + 1 );
    std::iota( baseTour.begin(), baseTour.end(), 1 );
    baseTour[ this->problem.numCities ] = 1;

    GeneticUtils::shuffleVector( baseTour.begin() + 1, baseTour.end() - 1 );

    return baseTour;
}

TTPGAConfig::TTPGAConfig() : NUM_INDIVIDUALS( 0 ),
                             MAX_GENS_WITHOUT_IMPROV( 0 ),
                             TOURNAMET_SIZE( 0 ),
                             TOURNAMET_SIZE_CROSSOVER( 0 ),
                             SELECTION_NUM_ELITES( 0 ),
                             SELECTION_NUM_ELITES_CROSSOVER( 0 ),
                             MUTATION_NUM_ELITES( 0 ),
                             NUM_CUT_POINTS( 0 ),
                             ALPHA_PROBABILITY( 0.f ),
                             CONFIG_NAME( "" ) 
{}

std::string TTPGAConfig::toString() const
{
    return std::string( "NUM_INDIVIDUALS: " ) + std::to_string( this->NUM_INDIVIDUALS ) + "\n"
         + std::string( "MAX_GENS_WITHOUT_IMPROV: " ) + std::to_string( this->MAX_GENS_WITHOUT_IMPROV ) + "\n"
         + std::string( "MAX_EXEC_TIME: " ) + std::to_string( this->MAX_EXEC_TIME.count() ) + "\n"
         + std::string( "TOURNAMET_SIZE: " ) + std::to_string( this->TOURNAMET_SIZE ) + "\n"
         + std::string( "TOURNAMET_SIZE_CROSSOVER: " ) + std::to_string( this->TOURNAMET_SIZE_CROSSOVER ) + "\n"
         + std::string( "SELECTION_NUM_ELITES: " ) + std::to_string( this->SELECTION_NUM_ELITES ) + "\n"
         + std::string( "SELECTION_NUM_ELITES_CROSSOVER: " ) + std::to_string( this->SELECTION_NUM_ELITES_CROSSOVER ) + "\n"
         + std::string( "MUTATION_NUM_ELITES: " ) + std::to_string( this->MUTATION_NUM_ELITES ) + "\n"
         + std::string( "NUM_CUT_POINTS: " ) + std::to_string( this->NUM_CUT_POINTS ) + "\n"
         + std::string( "ALPHA_PROBABILITY: " ) + std::to_string( this->ALPHA_PROBABILITY ) + "\n"
         + std::string( "CONFIG_NAME: " ) + this->CONFIG_NAME;
}

TTPGAConfig TTPGAConfig::readTTPGAConfigFromFile( std::string fileNamePath )
{
    std::ifstream file( fileNamePath );
    TTPGAConfig gaConf;
    std::string tmpString;

    unsigned short count = 0;

    if( file.is_open() )
    {
        file >> tmpString;    
        while( !file.eof() )
        {
            if( tmpString == "NUM_INDIVIDUALS:" )
            {
                file >> tmpString;
                gaConf.NUM_INDIVIDUALS = static_cast< unsigned >( std::stoul( tmpString ) );
                count++;
            } else if( tmpString == "MAX_GENS_WITHOUT_IMPROV:" )
            {
                file >> tmpString;
                gaConf.MAX_GENS_WITHOUT_IMPROV = static_cast< unsigned >( std::stoul( tmpString ) );
                count++;
            } else if( tmpString == "MAX_EXEC_TIME:" )
            {
                file >> tmpString;
                gaConf.MAX_EXEC_TIME = std::chrono::milliseconds( std::stoul( tmpString ) );
                count++; 
            } else if( tmpString == "TOURNAMET_SIZE:" )
            {
                file >> tmpString;
                gaConf.TOURNAMET_SIZE = std::stoull( tmpString );
                count++;
            } else if( tmpString == "TOURNAMET_SIZE_CROSSOVER:" )
            {
                file >> tmpString;
                gaConf.TOURNAMET_SIZE_CROSSOVER = std::stoull( tmpString );
                count++;
            } else if( tmpString == "SELECTION_NUM_ELITES:" )
            {
                file >> tmpString;
                gaConf.SELECTION_NUM_ELITES = std::stoull( tmpString );
                count++;
            } else if( tmpString == "SELECTION_NUM_ELITES_CROSSOVER:" )
            {
                file >> tmpString;
                gaConf.SELECTION_NUM_ELITES_CROSSOVER = std::stoull( tmpString );
                count++;
            } else if( tmpString == "MUTATION_NUM_ELITES:" )
            {
                file >> tmpString;
                gaConf.MUTATION_NUM_ELITES = std::stoull( tmpString );
                count++;
            } else if( tmpString == "NUM_CUT_POINTS:" )
            {
                file >> tmpString;
                gaConf.NUM_CUT_POINTS = static_cast< unsigned >( std::stoul( tmpString ) );
                count++;
            } else if( tmpString == "ALPHA_PROBABILITY:" )
            {
                file >> tmpString;
                gaConf.ALPHA_PROBABILITY = std::stof( tmpString );
                count++;
            } else if( tmpString == "CONFIG_NAME:" )
            {
                file >> tmpString;
                gaConf.CONFIG_NAME = tmpString;
                count++;
            }

            file >> tmpString;
        }
    }

    if( count < 11 )
    {
        throw std::invalid_argument( std::string( "The configuration file " ) + fileNamePath +
                                     " does not have enough parameters to fill TTPGAConfig" );
    }

    return gaConf;
}
