#include "ttpga.hpp"

TTPGA::TTPGA() : outputDirectory( "" ) {}

void TTPGA::run( unsigned numIndividuals,
                 unsigned numGenerations )
{
    if( numIndividuals % 2 != 0 )
    {
        throw std::invalid_argument( "numIndividuals must to be an even number" );
    }
    if( !this->problem.isLoaded )
    {
        throw std::logic_error( "Problem is not loaded yet!" );
    }

#if defined( __GA_PLOT_ ) || defined( __GA_LOG_ )
    std::string stringSpecs = std::string( "i=" ) + std::to_string( numIndividuals ) +
                              "-ng="    + std::to_string( numGenerations ) +
                              "-ts_s="  + std::to_string( this->gaConfig.TOURNAMET_SIZE ) +
                              "-ne_s="  + std::to_string( this->gaConfig.SELECTION_NUM_ELITES ) +
                              "-sne_c=" + std::to_string( this->gaConfig.SELECTION_NUM_ELITES_CROSSOVER ) +
                              "-ts_c="  + std::to_string( this->gaConfig.TOURNAMET_SIZE_CROSSOVER ) +
                              "-nc_c="  + std::to_string( this->gaConfig.NUM_CUT_POINTS ) +
                              "-a_m="   + std::to_string( this->gaConfig.ALPHA_PROBABILITY ) +
                              "-ne_m="  + std::to_string( this->gaConfig.MUTATION_NUM_ELITES );

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
    rec.writeInLogFile( "GA_specs", stringSpecs );
    rec.writeInLogFile(  "\"individuals\" : {\n\n" );
#endif // __GA_LOG_
#ifdef __GA_PLOT_
    stringSpecs += std::string( "  " ) + this->problem.probFileName;
#endif // __GA_PLOT_

    // std::function< std::vector< TTPIndividual >( const std::vector< TTPIndividual >& ) > 
    auto mutFunc = std::bind( TTPMutationMethod::twoOpt_bitFlip, 
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

    this->population = this->generatePopulation( numIndividuals );
    this->problem.evaluateIndividuals( this->population );

    for( unsigned i = 1; i <= numGenerations; i++ )
    {
        //** Selection Step **//
        this->population = SelectionMethod::generic_elitism( this->population,
                                                             this->gaConfig.SELECTION_NUM_ELITES_CROSSOVER,
                                                             numIndividuals ,
                                                             selFunc );

        //** Crossover Step **//
        std::vector< TTPIndividual > children = TTPCrossoverMethod::orderBased_alternate( this->population,
                                                                                          this->gaConfig.NUM_CUT_POINTS );
        this->population.insert( this->population.end(), children.begin(), children.end() );
        this->problem.evaluateIndividuals( this->population );
        this->population = SelectionMethod::generic_elitism( this->population,
                                                             this->gaConfig.SELECTION_NUM_ELITES_CROSSOVER,
                                                             numIndividuals ,
                                                             selFunc_cross );

        //** Mutation Step **//
        this->population = MutationMethods::generic_elitism( this->population, 
                                                             this->gaConfig.MUTATION_NUM_ELITES,
                                                             mutFunc );

        //** Evaluation Step **//
        this->problem.evaluateIndividuals( this->population );

        TTPIndividual best = this->getBestNIndividuals( 1 )[ 0 ];
#ifdef __GA_DETAILED_COUT_
        std::cout << "Generation " << i << " processed." << std::endl;
        std::cout << "Fitness of the best individual: " << best.fitness << std::endl;
        auto milliExecTime = std::chrono::duration_cast< std::chrono::milliseconds >
                                                       ( std::chrono::steady_clock::now() - this->startTime );
        std::cout << "Execution time: " << milliExecTime.count() << " milliseconds" << std::endl;
#endif __GA_DETAILED_COUT_
#ifdef __GA_PLOT_
        rec.recordIndFitnessToFileFit( best );
#endif //__GA_PLOT_
#ifdef __GA_LOG_
        rec.recordIndFitnessToFileLog( best );
#endif // __GA_LOG_
    }
    this->stopTimer();
#ifdef __GA_LOG_
    rec.writeInLogFile( "\n}");
    rec.closeFileLog();
#endif // __GA_LOG_
#ifdef __GA_PLOT_
    rec.plot( "plotGAData.gp", this->gaConfig.CONFIG_NAME );
#endif //__GA_PLOT_
}

std::vector< TTPIndividual > TTPGA::generatePopulation( unsigned numIndividuals )
{
    std::vector< TTPIndividual > population;
    population.reserve( numIndividuals );

    for( unsigned i = 0; i < numIndividuals; i++ )
    {
        TTPIndividual individual;


        //** Generating TSP component **//
        individual.features.tour = this->getLinkernTour( "lk.tour.temp" );


        //** Generating KP component **//
        individual.features.pickingPlan = std::vector< unsigned short >( this->problem.numItems, 0 );


        population.push_back( individual );
    }

    return population;
}

std::vector< unsigned long > TTPGA::getLinkernTour( std::string lkOutFileNamePath )
{
    std::string command;
    std::vector< unsigned long > tour;

    tour.reserve( this->problem.numCities + 1 );

#ifdef _MSC_VER
    command = "linkern.exe";
#else
    command = "linkern";
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
    std::remove( lkOutFileNamePath.c_str() );
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
                             NUM_GENERATIONS( 0 ),
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
         + std::string( "NUM_GENERATIONS: " ) + std::to_string( this->NUM_GENERATIONS ) + "\n"
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
            } else if( tmpString == "NUM_GENERATIONS:" )
            {
                file >> tmpString;
                gaConf.NUM_GENERATIONS = static_cast< unsigned >( std::stoul( tmpString ) );
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

    if( count < 10 )
    {
        throw std::invalid_argument( std::string( "The configuration file " ) + fileNamePath +
                                     " does not have enough parameters to fill TTPGAConfig" );
    }

    return gaConf;
}