#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include "logger.h"

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

    void logeMe()
    {
        for( int i = 0 ; i < rowsCount ; i++ )
        {
            char temp[ 1000 ];
            sprintf( temp, "X: %i, Y: %i, Gracz: %i\n", moves.at( i ).posX, moves.at( i ).posY, moves.at( i ).who );
            Logger::log( temp );
        }
    }
};

class Helper
{
public:
    static ConnectionData connectionData( int argc, char * argv[] );
    static ReceivedSignalData decodeSignal( const char * msg );
    static void encodeSignal( char x, char y, char player, char * resultSignal );
    static int toInt( char a1, char a2 );
    static void next( char & a1, char & a2, const char * & msg );
};

#endif // HELPER_H
