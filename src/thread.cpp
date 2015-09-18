#include "thread.h"

namespace QtPth
{

Thread::Thread(QObject *parent) :
    QObject(parent)
{
    pth_attr_t attr = pth_attr_new();
    pth_attr_set(attr, PTH_ATTR_NAME, "ticker");
    pth_attr_set(attr, PTH_ATTR_STACK_SIZE, 64*1024);
    pth_attr_set(attr, PTH_ATTR_JOINABLE, FALSE);
    pth_spawn(attr, &Thread::pthRun, this);
}


void Thread::sleep(quint32 secs)
{
    pth_sleep(secs);
}


Thread* Thread::spawn()
{
    Thread* thread = new Thread(this);
    return thread;
}


void Thread::run()
{
    WLOG("Empty thread is ran");
}


void* Thread::pthRun(void* ctx)
{
    static_cast<Thread*>(ctx)->run();
}

}

