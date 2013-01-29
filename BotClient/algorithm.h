#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QString>
#include "helper.h"

struct Element
{
    int m_player;
};

class Algorithm
{
public:
    Algorithm();

    const char * processResponse( const char * response );

private:
    QString m_playerResponse;
    Element m_matrix[ 30 ][ 40 ];

    void buildMatrix();
    void updateMatrix( ReceivedSignalData & rcData );
    vector< std::pair< int, int > > validMoves() const;
    bool hasNeighbour( int row, int column ) const;
};

#endif // ALGORITHM_H
