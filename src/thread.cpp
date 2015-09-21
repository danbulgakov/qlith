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

Thread* Thread::current()
{
//    pth_t th = pth_self();
//    pth_attr_t attr = pth_attr_of(th);
//    pth_attr_get(attr, PTH_ATTR_START_ARG);
//    mThread = pth_spawn(attr, &Thread::pthRun, this);
//    PTH_ATTR_START_ARG
}

void Thread::except(std::exception& e)
{
    WLOG("Exception is thrown: %1", e.what());
}

void* Thread::pthRun(void* ctx)
{
    static_cast<Thread*>(ctx)->run();
}

void Thread::run()
{
    try
    {
        mHandler();
    }
    catch(std::exception& e)
    {
        except(e);
    }
    if(mDestroyOnDone)
        deleteLater();
}

}

