#include <stdlib.h>
#include <stdio.h>
#include "helper.h"
#include "exc.h"
#include "connection.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    Connection * conn;

    try
    {
        conn = new Connection( Helper::connectionData( argc, argv ) );
        conn->startConnection();
    }
    catch( EXC::Exception e )
    {
        Logger::log( e.what() );
        exit( 1 );
    }

    return 0;
}

