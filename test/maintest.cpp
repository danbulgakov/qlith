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


MainTest::~MainTest()
{
    QtPth::free();
}


void MainTest::run(const QString& value)
{
    qDebug() << "RUN:" << value;
    //while(true) QtPth::Thread::current();
    qDebug() << "DONE:" << value;
}


void MainTest::simpleTestCase()
{
    QtPth::Thread* th = QtPth::Thread::spawn(this, this, &MainTest::run, "Main");
    QtPth::Thread::spawn(th, this, &MainTest::run, "Child-1");
    QtPth::Thread::spawn(th, this, &MainTest::run, "Child-2");
    Thread::sleep(1);
}


}
