#ifndef INDIVIDUALRECORDER_HPP
#define INDIVIDUALRECORDER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "individualrecorder.hpp"

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
    void recordIndFitnessToFile( const T& individual );

};

#endif // INDIVIDUALRECORDER_HPP
