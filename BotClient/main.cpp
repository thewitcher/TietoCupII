#include <stdlib.h>
#include <stdio.h>
#include "helper.h"
#include "exc.h"
#include "connection.h"

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
        qDebug() << e.what();
        exit( 1 );
    }

    return 0;
}

