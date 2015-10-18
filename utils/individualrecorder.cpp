#include "individualrecorder.hpp"

IndividualRecorder::IndividualRecorder() : numRecordedInd( 0 ) {}

void IndividualRecorder::setDestinationFile( const std::string& fileName )
{
    this->destinationFile = fileName;
}

std::string IndividualRecorder::getSuffixDateTime()
{
    std::stringstream out;
    std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t( now );
    out << std::put_time( std::localtime( &now_t ), "%Y-%m-%d_%H-%M-%S" );
    return out.str();
}

void IndividualRecorder::plot( std::string gnuplotScript, std::string dataTitle )
{
    // gnuplot -e "filename='2015-10-02_20-44-26__120_3_2_2.dat'; datatitle='120_3_2_2'" plotGAData.gp
    std::string command;
    command ="gnuplot -e \"";
    command += std::string( "filename='" ) + this->destinationFile + "'; ";
    command += std::string( "datatitle='" ) + dataTitle + "' ";
    command += "\" ";
    command += gnuplotScript;

    std::system( command.c_str() );
}
