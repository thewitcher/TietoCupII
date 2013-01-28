#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "connection.h"
#include "exc.h"
#include "algorithm.h"

Connection::Connection( const ConnectionData & data ):
    m_data( data ),
    m_socketFileDescriptor( -1 ),
    c_maxReceivedDataSize( 4096 ),
    m_algorithm( new Algorithm )
{}

Connection::~Connection()
{
    delete m_algorithm;
    close( m_socketFileDescriptor );
}

// Get socket address, IPv4 or IPv6:
void * Connection::get_in_addr( struct sockaddr * socketAddress )
{
    if ( socketAddress->sa_family == AF_INET ) // ip ver 4
    {
        return & ( ( ( struct sockaddr_in * ) socketAddress )->sin_addr );
    }

    // ip ver 6
    return & ( ( ( struct sockaddr_in6 * ) socketAddress )->sin6_addr );
}

void Connection::initConnection()
{
    struct addrinfo hints;
    struct addrinfo * servinfo;
    struct addrinfo * p;
    int rv;

    char s[ INET6_ADDRSTRLEN ];

    memset( & hints, 0, sizeof( hints ) ); // Set null for hints
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if( ( rv = getaddrinfo( m_data.address.c_str() /*ip address*/, m_data.port.c_str() /*port*/, & hints, & servinfo ) ) != 0 )
    {
        char temp[ 200 ];
        sprintf( temp, "Function getaddrinfo has failed (ip ddress: %s)", m_data.address.c_str() );
        throw EXC::Exception( temp );
    }

    // Loop through all the results and connect to the first we can
    for( p = servinfo ; p != NULL ; p = p->ai_next )
    {
        if( ( m_socketFileDescriptor = socket( p->ai_family, p->ai_socktype, p->ai_protocol ) ) == -1 )
        {
            qDebug() << "Cannot create client socket";
            continue;
        }

        if ( connect( m_socketFileDescriptor, p->ai_addr, p->ai_addrlen ) == -1 )
        {
            close( m_socketFileDescriptor );
            perror( "Client: connect" );
            continue;
        }

        break;
    }

    if ( p == NULL )
    {
        throw EXC::Exception( "Connextion couldn't be established" );
    }

    inet_ntop( p->ai_family, get_in_addr( ( struct sockaddr * ) p->ai_addr ), s, sizeof( s ) );
    qDebug() << "Client: connecting to the server";

    freeaddrinfo( servinfo ); // All done with this structure, so delete all
}

void Connection::startConnection()
{
    if( m_socketFileDescriptor == -1 )
    {
        initConnection();
    }

    int numberOfBytes; // Number of bytes received from server
    char buf[ c_maxReceivedDataSize ]; // Buffer for received message

    while( 1 )
    {
        if ( ( numberOfBytes = recv( m_socketFileDescriptor, buf, c_maxReceivedDataSize - 1, 0 ) ) == -1 )
        {
            perror( "recv" );
            exit( 1 );
        }

        buf[ numberOfBytes ] = '\0'; // Buffer with received signal

        send(  m_socketFileDescriptor, m_algorithm->processResponse( buf ), 100, 0 ); // Here we send response from player
        Helper::decodeSignal( buf );
    }
}
