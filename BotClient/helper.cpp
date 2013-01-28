#include <stdlib.h>
#include <iostream>
#include "helper.h"
#include "exc.h"
#include <logger.h>

ConnectionData Helper::connectionData( int argc, char * argv[] )
{
    ConnectionData cd;

    int opt = 0;
    while( ( opt = getopt( argc, argv, "h:p:g:") ) != -1  )
    {
        switch( opt)
        {
        case 'h':
            cd.address = optarg;
            break;
        case 'p':
            cd.port = optarg;
            break;
        case 'g':
            cd.playerNumber = atoi( optarg );
            break;
        }
    }

    if( cd.isDataValid() == false )
    {
        throw EXC::Exception( "Application parameters are invalid" );
    }

    return cd;
}

ReceivedSignalData Helper::decodeSignal( const char * msg )
{
    if( msg == NULL)
    {
        throw EXC::Exception( "Received message is null" );
    }

    char temp[ 200 ];
    sprintf( temp, "Receved message <%s>", msg );
    Logger::log( msg );

    ReceivedSignalData rcData;

    char a1;
    char a2;

    Helper::next( a1, a2, msg );
    rcData.rowsCount = Helper::toInt( a1, a2 );

    for( int i = 0 ; i < rcData.rowsCount ; i++ )
    {
        Coordinates c;

        Helper::next( a1, a2, msg );
        c.posX = Helper::toInt( a1, a2 );
        Helper::next( a1, a2, msg );
        c.posY = Helper::toInt( a1, a2 );
        Helper::next( a1, a2, msg );
        c.who = Helper::toInt( a1, a2 );

        rcData.moves.push_back( c );
    }

    rcData.logeMe();

    return rcData;
}

void Helper::encodeSignal( char x, char y, char player, char * resultSignal )
{
    * resultSignal = x;
    * ( resultSignal + 1 ) = ' ';
    * ( resultSignal + 2 ) = y;
    * ( resultSignal + 3 ) = ' ';
    * ( resultSignal + 4 ) = player;
    * ( resultSignal + 5 ) = '\n';
    * ( resultSignal + 6 ) = '\0';
}

int Helper::toInt( char a1, char a2 )
{
    cout << "<" << a1 << ">, <" << a2 << ">" << endl;

    if( ( a2 < 48 ) ||  ( a2 > 57 ) )
    {
        return ( a1 - 48 );
    }

    return ( ( a1 - 48 ) * 10 + ( a2 - 48 ) );
}

void Helper::next( char & a1, char & a2, const char * & msg )
{
    a1 = * ( msg++ );
    a2 = * ( msg++ );
}
