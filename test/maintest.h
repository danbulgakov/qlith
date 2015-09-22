#ifndef MAINTEST_H
#define MAINTEST_H

#include <QObject>
#include <QtTest>

#include <exception>
#include <stdexcept>

#include "qtpth.h"
#include "logger.h"
#include "thread.h"


namespace QtPth
{

class MainTest : public QObject
{
    Q_OBJECT
public:
    static void logHandler(Logger::Priority priority,
                           const QString& category,
                           const QString& sender,
                           const QString& text);
    virtual ~MainTest();
    void run(const QString& value);
    void exceptRun(const QString& value);
    void except(const ExecutionException& e,
                const QString& value);

public:
    explicit MainTest(QObject *parent = 0);

private slots:
     void simpleTestCase();
};

}
#endif // MAINTEST_H
