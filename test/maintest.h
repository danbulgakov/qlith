#ifndef MAINTEST_H
#define MAINTEST_H

#include <QObject>
#include <QtTest>

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

public:
    explicit MainTest(QObject *parent = 0);

private slots:
     void simpleTestCase();
};

}
#endif // MAINTEST_H
