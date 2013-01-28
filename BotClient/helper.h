#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
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
    int posX;
    int posY;
    int who;
};

struct ReceivedSignalData
{
    // order is very important here

    // how many rows is in received signal
    int rowsCount;

    // if true then player has created a base
    bool isBaseCreated;

    // base points coordinates
    vector< Coordinates > moves;
};

class Helper
{
public:
    static ConnectionData connectionData( int argc, char * argv[] );
    static ReceivedSignalData decodeSignal( const char * msg );
    static const QString encodeSignal( int x, int y, int player );
};

#endif // HELPER_H
