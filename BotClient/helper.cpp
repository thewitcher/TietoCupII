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

    for( int i = 0 ; i < rcData.rowsCount ; i++ ) // the last one could be base description, so I treat it particularly
    {
        if( splitedMsgString.at( i + 1 ).at( 0 ) == 'B' ) // if first letter is "B" then it describes base points
        {
            QStringList base = splitedMsgString.at( i + 1 ).split( '\t' );
            QStringList baseData = base.at( 0 ).split( " " );
            vector< pair< int,int > > vec;

            for( int point = 0 ; point < baseData.at( 1 ).toInt() ; point++ )
            {
                QStringList basePoint = base.at( point + 1 ).split( ' ' );
                pair< int, int > p( basePoint.at( 0 ).toInt(), basePoint.at( 1 ).toInt() );
                vec.push_back( p );
            }

            rcData.basePoint.insert( make_pair( baseData.at( 2 ).toInt(), vec ) );
        }
        else
        {
            Coordinates c;
            QStringList line = splitedMsgString.at( i + 1 ).split( ' ' );

            c.column = line.at( 0 ).toInt();
            c.row = line.at( 1 ).toInt();
            c.who = line.at( 2 ).toInt();
            rcData.moves.push_back( c );
        }
    }

    return rcData;
}

const QString Helper::encodeSignal( int x, int y, int player )
{
    QString result = QString::number( x ) + " " + QString::number( y )+ " " + QString::number( player ) + "\n";

    return result;
}
