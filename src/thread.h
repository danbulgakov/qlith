#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <exception>

#include "global.h"
#include "logger.h"
#include "pth.h"


using namespace std;

namespace QtPth
{

class QTSHAREDLIB_EXPORT Thread : public QObject
{
    Q_OBJECT
    DECLARE_LOG_CAT(thread);

public:   
    static void sleep(quint32 secs);

    template<typename Object, typename Method, typename ... Args>
    static Thread* spawn(QObject* parent, Object object,
                         Method handler, Args ... args);
    static Thread* current();

public:
    Thread(bool destroyOnDone = true,
           QObject *parent = 0);
    virtual ~Thread();

    template<typename Object, typename Method, typename ... Args>
    void start(Object object, Method handler, Args ... args);
    void yield();

protected:
    virtual void except(exception& e);

private:
    static void* pthRun(void* ctx);
    void run();

private:
    pth_t mThread;
    bool mDestroyOnDone;
    function<void()> mHandler;
};


template<typename Object, typename Method, typename ... Args>
Thread* Thread::spawn(QObject* parent, Object object,
                      Method handler, Args ... args)
{
    Thread* thread = new Thread(true, parent);
    thread->start(object, handler, args ...);
    return thread;
}

template<typename Object, typename Method, typename ... Args>
void Thread::start(Object object, Method handler, Args ... args)
{
    Q_ASSERT(!mThread);
    mHandler = bind(handler, object, args...);
    pth_attr_t attr = pth_attr_new();
    pth_attr_set(attr, PTH_ATTR_NAME, "ticker");
    pth_attr_set(attr, PTH_ATTR_STACK_SIZE, 64*1024);
    pth_attr_set(attr, PTH_ATTR_JOINABLE, TRUE);
    mThread = pth_spawn(attr, &Thread::pthRun, this);
}


}

#endif // THREAD_H
