#ifndef MAINTEST_H
#define MAINTEST_H

#include <QObject>
#include <QtTest>

#include <exception>
#include <stdexcept>

#include "qtpth.h"
#include "logger.h"
#include "thread.h"
#include "testutils.h"


namespace QtPth
{

class MainTest : public QObject
{
    Q_OBJECT
    DECLARE_LOG_CAT("main_test");
public:
    static void logHandler(Logger::Priority priority,
                           const QString& category,
                           const QString& sender,
                           const QString& text);
    virtual ~MainTest();
    void run(const QString& value);
    void yieldRun(const QString& value);
    void loop(const QString& value);

    void exceptRun(const QString& value);
    void except(const ExecutionException& e,
                const QString& value);

public:
    explicit MainTest(QObject *parent = 0);

private slots:
     void simpleYieldTestCase();
     void loopExitTestCase();
     void exceptionTestCase();

private:
     struct RunEntity
     {
        QString method;
        QString value;
        QString toString() const
        {
            return Debug::format("Entity(%1:%2)",
                                 method, value);
        }
     };
private:

     QList<RunEntity> mRuns;
};

}
#endif // MAINTEST_H
