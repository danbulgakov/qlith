#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

#include <exception>

#include "debug.h"


using namespace std;
namespace QtPth
{

class Exception: public exception
{
public:
    template<typename ... Args>
    Exception(Args ...  args);
    virtual ~Exception() throw();
    virtual const char* what() const throw();

protected:
    QByteArray mMessage;
};


template<typename ... Args>
Exception::Exception(Args ... args) :
    mMessage(Debug::format(args...).toAscii())
{
}


class ExecutionException: public Exception
{
public:
    template<typename ... Args>
    ExecutionException(const exception& cause,
                       Args ... args);
    virtual ~ExecutionException() throw();
    const exception& cause() const;
    QString toString() const;

private:
    const exception& mCause;
};


template<typename ... Args>
ExecutionException::ExecutionException(
        const exception& cause, Args ... args) :
    Exception(args...),
    mCause(cause)
{
}

}
#endif // EXCEPTION_H
