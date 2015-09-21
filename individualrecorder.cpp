#include "individualrecorder.hpp"

IndividualRecorder::IndividualRecorder() : numIndRecorded( 0 ) {}

void IndividualRecorder::setDestinationFile( const std::string& fileName )
{
    this->destinationFile = fileName;
}

template< class T >
void IndividualRecorder::recordIndFitnessToFile( const T& individual )
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
