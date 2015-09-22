#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <exception>

#include "global.h"
#include "logger.h"
#include "pth.h"
#include "exception.h"


using namespace std;
using namespace placeholders;

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

    static Thread* create(QObject* parent,
                          bool destroyOnDone = true);
    static Thread* current();

public:
    Thread(bool destroyOnDone = true,
           QObject *parent = 0);
    virtual ~Thread();

    template<typename Object, typename Method, typename ... Args>
    Thread* start(Object object, Method handler, Args ... args);

    template<typename Object, typename Method, typename ... Args>
    Thread* except(Object object, Method handler, Args ... args);

    void yield();
    void kill();

private:
    static void* pthRun(void* ctx);
    void run();

private:
    pth_t mThread;
    bool mDestroyOnDone;
    function<void()> mHandler;
    function<void(const ExecutionException&)> mExcept;
};


template<typename Object, typename Method, typename ... Args>
Thread* Thread::except(Object object, Method handler,
                       Args ... args)
{
    mExcept = bind(handler, object, _1, args...);
    return this;
}

template<typename Object, typename Method, typename ... Args>
Thread* Thread::spawn(QObject* parent, Object object,
                      Method handler, Args ... args)
{
    Thread* thread = new Thread(true, parent);
    return thread->start(object, handler, args ...);
}

template<typename Object, typename Method, typename ... Args>
Thread* Thread::start(Object object, Method handler, Args ... args)
{
    Q_ASSERT(!mThread);
    mHandler = bind(handler, object, args...);
    pth_attr_t attr = pth_attr_new();
    QByteArray name = Utils::strPtr(this).toAscii();
    pth_attr_set(attr, PTH_ATTR_NAME, name.constData());
    pth_attr_set(attr, PTH_ATTR_STACK_SIZE, 64 * 1024);
    pth_attr_set(attr, PTH_ATTR_JOINABLE, TRUE);
    mThread = pth_spawn(attr, &Thread::pthRun, this);
    return this;
}


}

#endif // THREAD_H
