#include <fstream>
#include "logger.h"
#include "exc.h"

Logger::Logger()
{
    // There is no need to implement any constructor. Everything has done in macro.
}

Logger::~Logger()
{}

void Logger::log( const char * info )
{
#ifdef LOGGER
    static bool first = true;

    std::ofstream outfile;

    if( first == true )
    {
        outfile.open( "log.txt", std::ios_base::trunc );
        outfile.close();
        first = false;
    }

    outfile.open( "log.txt", std::ios_base::app );
    outfile << info << "\n";
    outfile.close();
#else
    ( void ) info;
#endif
}
