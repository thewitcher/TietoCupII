#ifndef EXC_H
#define EXC_H

namespace EXC
{
    class Exception
    {
    public:
        Exception( const char * msg ):
            m_msg( msg )
        {}

        const char * what() const
        {
            return m_msg;
        }

    private:
        const char * m_msg;
    };
}

#endif // EXC_H
