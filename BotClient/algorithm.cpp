#include "algorithm.h"
#include <iostream>

Algorithm::Algorithm():
    m_playerResponse( new char[ 4096 ] )
{
    buildMatrix();
}

const char * Algorithm::processResponse( const char * response )
{
    // decoded signal from server
    ReceivedSignalData rcData = Helper::decodeSignal( response );

    updateMatrix( rcData );

    m_playerResponse = Helper::encodeSignal( 2, 2, 2 );

    return m_playerResponse.toAscii().data();
}

void Algorithm::buildMatrix()
{
    for( int row = 0 ; row < 40 ; row++ )
    {
        for( int column = 0 ; column < 30 ; column++ )
        {
            m_matrix[ row ][ column ].m_player = 0;
        }
    }
}

void Algorithm::updateMatrix( ReceivedSignalData & rcData )
{
    for( int i = 0 ; i < rcData.rowsCount; i++ )
    {
        m_matrix[ rcData.moves.at( i ).posY - 1 ][ rcData.moves.at( i ).posX - 1 ].m_player = rcData.moves.at( i ).who;
    }

    for( int row = 0 ; row < 40 ; row++ )
    {
        for( int column = 0 ; column < 30 ; column++ )
        {
            cout << m_matrix[ row ][ column ].m_player << " ";
        }
        cout << endl;
    }
}
