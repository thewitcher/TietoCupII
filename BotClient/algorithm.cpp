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
    vector< std::pair< int, int > > valid = validMoves();

    std::pair< int, int > firstValid = valid.at( 0 );

    m_playerResponse = Helper::encodeSignal( firstValid.second, firstValid.first, 2 );

    return m_playerResponse.toAscii().data();
}

void Algorithm::buildMatrix()
{
    for( int row = 0 ; row < 30 ; row++ )
    {
        for( int column = 0 ; column < 40 ; column++ )
        {
            m_matrix[ row ][ column ].m_player = 0;
        }
    }
}

void Algorithm::updateMatrix( ReceivedSignalData & rcData )
{
    for( int i = 0 ; i < rcData.rowsCount; i++ )
    {
        m_matrix[ rcData.moves.at( i ).row - 1 ][ rcData.moves.at( i ).column - 1 ].m_player = rcData.moves.at( i ).who;
    }
}

vector< std::pair< int, int > > Algorithm::validMoves() const
{
    vector< std::pair< int, int > > temp;

    for( int row = 0 ; row < 30 ; row++ )
    {
        for( int column = 0 ; column < 40 ; column++ )
        {
            if( m_matrix[ row ][ column ].m_player == 0 )
            {
                if( hasNeighbour( row, column ) == true )
                {
                    temp.push_back( std::pair< int, int >( row + 1, column + 1 ) ); // because matrix and game are moved by one point
                }
            }
        }
    }

    return temp;
}

bool Algorithm::hasNeighbour( int row, int column ) const
{
    if( ( row - 1 >= 0 ) && ( column - 1 >= 0 ) )
    {
        if( m_matrix[ row - 1 ][ column - 1 ].m_player != 0  )
        {
            return true;
        }
    }
    if( row - 1 >= 0 )
    {
        if( m_matrix[ row ][ column - 1 ].m_player != 0  )
        {
            return true;
        }
    }
    if( ( row - 1 >= 0 ) && ( column + 1 < 40 ) )
    {
        if( m_matrix[ row - 1 ][ column + 1 ].m_player != 0  )
        {
            return true;
        }
    }
    if( column - 1 >= 0 )
    {
        if( m_matrix[ row ][ column - 1 ].m_player != 0  )
        {
            return true;
        }
    }
    if( column + 1 < 40 )
    {
        if( m_matrix[ row ][ column + 1 ].m_player != 0  )
        {
            return true;
        }
    }
    if( ( row + 1 < 30 ) && ( column - 1 >= 0 ) )
    {
        if( m_matrix[ row + 1 ][ column - 1 ].m_player != 0  )
        {
            return true;
        }
    }
    if( row + 1 < 30 )
    {
        if( m_matrix[ row + 1 ][ column ].m_player != 0  )
        {
            return true;
        }
    }
    if( ( row + 1 < 30 ) && ( column + 1 < 40 ) )
    {
        if( m_matrix[ row + 1 ][ column + 1 ].m_player != 0  )
        {
            return true;
        }
    }

    return false;
}
