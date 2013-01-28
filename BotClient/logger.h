#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <stdio.h>

class Logger
{
public:
    static void log( const char * info );

private:
    Logger();
    ~Logger();
};

#endif // LOGGER_H
