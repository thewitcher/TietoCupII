#ifndef CONNECTION_H
#define CONNECTION_H

#include "helper.h"

class Algorithm;

class Connection
{
public:
    Connection( const ConnectionData & data );
    ~Connection();

    void initConnection();
    void startConnection();

private:
    const ConnectionData m_data;
    int m_socketFileDescriptor; // File descriptor for new socket. -1 if there is no valid socket
    const int c_maxReceivedDataSize;
    Algorithm * m_algorithm;

    void * get_in_addr( struct sockaddr * socketAddress );
};

#endif // CONNECTION_H
