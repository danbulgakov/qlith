#include "pool.h"

namespace QLith
{

Pool::Pool(qint32 threads, QObject *parent) :
    QObject(parent),
    mMaxThreads(threads)
{
}

Thread* Pool::run()
{
    if(mFree.isEmpty())
    {
        if(mThreads.size() >= mMaxThreads)
        {
            //TODO: Wait
        }
        else
        {
            //TODO: Create new
        }
    }
    else
    {
        //TODO: Take free
    }
    return NULL;
}

}
