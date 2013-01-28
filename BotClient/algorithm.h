#ifndef ALGORITHM_H
#define ALGORITHM_H

class Algorithm
{
public:
    Algorithm();

    void processResponse( const char * response );
    const char * playerResponse() const;

private:
    char * m_playerResponse;
};

#endif // ALGORITHM_H
