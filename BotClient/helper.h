#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <map>
#include <QString>
#include <QDebug>

using namespace std;

struct ConnectionData
{
    string address;
    string port;
    int playerNumber;

    bool isDataValid() const
    {
        return ( ( address.empty() == false ) && ( port.empty() == false ) && ( playerNumber > 0 ) );
    }
};

struct Coordinates
{
    int row;
    int column;
    int who;
};

struct ReceivedSignalData
{
    // how many rows is in received signal
    int rowsCount;

    // base points coordinates
    vector< Coordinates > moves;

    multimap< int, vector< pair< int, int > > > basePoint; // for each player there is a set of points that are created a base
};

class Helper
{
public:
    static ConnectionData connectionData( int argc, char * argv[] );
    static ReceivedSignalData decodeSignal( const char * msg );
    static const QString encodeSignal( int x, int y, int player );
};

#endif // HELPER_H
