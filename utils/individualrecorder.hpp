#ifndef INDIVIDUALRECORDER_HPP
#define INDIVIDUALRECORDER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <cstdlib>

class IndividualRecorder
{
private:
    /** Number of recorded individuals used for ordered index purposes. */
    unsigned numRecordedInd;
    /** File (path and name) taht will be used to write the \c fitness of the individuals. */
    std::string destinationFile;


public:
    /**
     * @brief IndividualRecorder        Constructor.
     */
    IndividualRecorder();
    /**
     * @brief setDestinationFile        Set the file name (with the path if necessary).
     *
     * @param fileName                  The file name that will be used to set
     *                                  \ref destinationFile variable.
     */
    void setDestinationFile( const std::string& fileName );
    /**
     * @brief recordIndFitnessToFile    Record the individual fitness to a
     *                                  file previously set.
     *
     * @param individual                Individual that will be recorded.
     */
    template< class T >
    void recordIndFitnessToFile( const T& individual )
    {
        std::ofstream outputFile( this->destinationFile, std::ios::app  );
        if( !outputFile )
        {
            std::cerr << "Cannot open the outputfile: " << this->destinationFile << std::endl;
            return;
        }

        this->numRecordedInd++;
        outputFile << std::to_string( this->numRecordedInd )
                   << " " << std::to_string( individual.fitness )
                   << "\n";

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
