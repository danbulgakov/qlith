#include "exception.h"
namespace QLith
{

Exception::~Exception() throw()
{

}

const char* Exception::what() const throw()
{
    return mMessage.constData();
}

ExecutionException::~ExecutionException() throw()
{
}

const exception& ExecutionException::cause() const
{
    return mCause;
}

QString ExecutionException::toString() const
{
    return Debug::format("Except(%1, cause: %2)",
                         mMessage, mCause);
}


}
