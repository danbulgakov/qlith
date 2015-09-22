#include "thread.h"

namespace QtPth
{

Thread::Thread(bool destroyOnDone,
               QObject *parent) :
    QObject(parent),
    mThread(NULL),
    mDestroyOnDone(destroyOnDone),
    mHandler(NULL)
{
}

Thread::~Thread()
{
    DLOG("Destroyed");
    if(mThread)
    {
        pth_join(mThread, NULL);
    }
}

void Thread::yield()
{
    Q_ASSERT(mThread);
    pth_yield(mThread);
}

void Thread::sleep(quint32 secs)
{
    pth_sleep(secs);
}

Thread* Thread::create(QObject* parent,
                       bool destroyOnDone)
{
    return new Thread(destroyOnDone, parent);
}

Thread* Thread::current()
{
    pth_t th = pth_self();
    Q_ASSERT(th);
    pth_attr_t attr = pth_attr_of(th);
    void* curTh = NULL;
    pth_attr_get(attr, PTH_ATTR_START_ARG, &curTh);
    Thread* result = static_cast<Thread*>(curTh);
    QTPTH_ASSERT(result, "Current thread was not started");
    return result;
}

void* Thread::pthRun(void* ctx)
{
    static_cast<Thread*>(ctx)->run();
}

void Thread::run()
{
    try
    {
        if(mHandler)
            mHandler();
        else
        {
            WLOG("Thread method is not specified");
        }
    }
    catch(std::exception& e)
    {
        if(mExcept)
            mExcept(ExecutionException(e, "Thread execution"));
        else
        {
            ELOG("Unhandled exception: %1", e);
        }
    }
    if(mDestroyOnDone)
        deleteLater();
}

}

