#ifndef POOL_H
#define POOL_H

#include <QObject>
#include <QList>

#include "thread.h"

namespace QLith
{

class Pool : public QObject
{
    Q_OBJECT
public:
    explicit Pool(qint32 threads,
                  QObject *parent = 0);
    Thread* run();

private:
    qint32 mMaxThreads;
    QList<Thread*> mThreads;
    QList<Thread*> mFree;
};

}

#endif // POOL_H
