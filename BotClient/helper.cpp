#include <stdlib.h>
#include <iostream>
#include <QStringList>
#include <QDebug>
#include "helper.h"
#include "exc.h"

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

    qDebug() << "Received message " << msg;

    ReceivedSignalData rcData;

    QString msgString( msg );
    QStringList splitedMsgString = msgString.split( '\n' );

    rcData.rowsCount = splitedMsgString.at( 0 ).toInt();

    for( int i = 0 ; i < rcData.rowsCount ; i++ )
    {
        Coordinates c;
        QStringList line = splitedMsgString.at( i + 1 ).split( ' ' );


        c.posX = line.at( 0 ).toInt();
        c.posY = line.at( 1 ).toInt();
        c.who = line.at( 2 ).toInt();

        rcData.moves.push_back( c );
    }

    return rcData;
}

const QString Helper::encodeSignal( int x, int y, int player )
{
    QString result = QString::number( x ) + " " + QString::number( y )+ " " + QString::number( player ) + "\n";

    return result;
}
