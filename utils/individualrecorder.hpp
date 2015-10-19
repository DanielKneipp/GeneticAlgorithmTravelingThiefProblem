#ifndef INDIVIDUALRECORDER_HPP
#define INDIVIDUALRECORDER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>    // std::time_t, std::localtime()
#include <cstdlib>  // std::system()

class IndividualRecorder
{
private:
    /** Number of recorded individuals used for ordered index purposes. */
    unsigned numRecordedIndLog;
    /** Number of recorded individuals (fitness only) used for ordered index purposes. */
    unsigned numRecordedIndFit;
    /** File (path and name) that will be used to write the \c fitness of the individuals. */
    std::string destinationFileFit;
    /** File (path and name) that will be used to write the individuals with all your features. */
    std::string destinationFileLog;


public:
    /**
     * @brief IndividualRecorder        Constructor.
     */
    IndividualRecorder();
    /**
     * @brief setDestinationFile        Set the file name (with the path if necessary)
     *                                  that will be used to store the individuals 
     *                                  (fitness only).
     *
     * @param fileName                  The file name that will be used to set
     *                                  \ref destinationFile variable.
     */
    void setDestinationFileFit( const std::string& fileName );
    /**
     * @brief setDestinationFile        Set the file name (with the path if necessary)
     *                                  that will be used to store the entire individual
     *                                  (with his features).
     *
     * @param fileName                  The file name that will be used to set
     *                                  \ref destinationFile variable.
     */
    void setDestinationFileLog( const std::string& fileName );
    /**
     * @brief prepareFileLog            Writes to the log file the
     *                                  start of structure.
     */
    void prepareFileLog();
    /**
     * @brief closeFileLog              Writes at the end of the log file 
     *                                  the end of structure.
     */
    void closeFileLog();
    /**
     * @brief recordIndFitnessToFileFit     Record the individual fitness to a
     *                                      file previously set.
     *
     * @param individual                    Individual that will be recorded.
     */
    template< class T >
    void recordIndFitnessToFileFit( const T& individual )
    {
        std::ofstream outputFile( this->destinationFileFit, std::ios::app );
        if( !outputFile )
        {
            std::cerr << "Cannot open the output file: " << this->destinationFileFit << std::endl;
            return;
        }

        this->numRecordedIndFit++;
        outputFile << std::to_string( this->numRecordedIndFit )
                   << " " << std::to_string( individual.fitness )
                   << "\n";

        outputFile.close();
    }
    /**
     * @brief recordIndFitnessToFileLog     Record the individual fitness to a
     *                                      file previously set.
     *
     * @param individual                    Individual that will be recorded.
     */
    template< class T >
    void recordIndFitnessToFileLog( const T& individual )
    {
        std::ofstream outputFile( this->destinationFileLog, std::ios::app );
        if( !outputFile )
        {
            std::cerr << "Cannot open the output file: " << this->destinationFileLog << std::endl;
            return;
        }

        this->numRecordedIndLog++;
        outputFile << "\"" << std::to_string( this->numRecordedIndLog ) << "\" : "
                   << individual.toString() << ","
                   << "\n\n";

        outputFile.close();
    }
    /**
     * @brief getSuffixDateTime         Generate a string with current ate and time.
     *
     * @return                          The string with the date and time.
     */
    static std::string getSuffixDateTime();
    /**
     * @brief plot                      Plot the stored data using GNUPlot.
     *
     * @param gnuplotScript             The GNUPlot script used to plot the data.
     *                                  must receive the parameters \c
     *                                  filename (name of the file that the data is stored)
     *                                  and \c datatitle (legend of the data).
     *
     * @param dataTitle                 The legend of the data.
     */
    void plot( std::string gnuplotScript, std::string dataTitle );
};

#endif // INDIVIDUALRECORDER_HPP
