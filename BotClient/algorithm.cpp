#include "algorithm.h"
#include "helper.h"


Algorithm::Algorithm():
    m_playerResponse( new char[ 4096 ] )
{}

void Algorithm::processResponse( const char * response )
{
    // decoded signal from server
    ReceivedSignalData rcData = Helper::decodeSignal( response );

    Helper::encodeSignal( '2', '2', '2', m_playerResponse );
}

const char * Algorithm::playerResponse() const
{
    return m_playerResponse;
}
