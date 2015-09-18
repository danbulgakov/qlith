#include "maintest.h"
namespace QtPth
{

MainTest::MainTest(QObject *parent) : QObject(parent)
{
    LG->addHandler(&QtPth::MainTest::logHandler);
    QtPth::init();
}


void QtPth::MainTest::logHandler(Logger::Priority priority,
                                 const QString& category,
                                 const QString& sender,
                                 const QString& text)
{
    qDebug() << Logger::priority(priority) << category << sender << "==>" << text;
}


void MainTest::simpleTestCase()
{
    QtPth::Thread th(this);
    Thread::sleep(4);
}


}
