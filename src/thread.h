#ifndef THREAD_H
#define THREAD_H

#include <QObject>

#include "global.h"
#include "logger.h"
#include "pth.h"


namespace QtPth
{

class QTSHAREDLIB_EXPORT Thread : public QObject
{
    Q_OBJECT
    DECLARE_LOG_CAT(thread);

public:   
    static void sleep(quint32 secs);
    Thread* spawn();

public:
    Thread(QObject *parent = 0);

protected:
    virtual void run();

private:
    static void* pthRun(void* ctx);
};

}

#endif // THREAD_H
