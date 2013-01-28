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
    Element m_matrix[ 40 ][ 30 ];

    void buildMatrix();
    void updateMatrix( ReceivedSignalData & rcData );
};

#endif // ALGORITHM_H
