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
    for(int i = 0; i < 5; i++)
    {
        //QtPth::Thread::current().yield();
        qDebug() << "TICK:" << value;
        QtPth::Thread::sleep(1);
    }
    qDebug() << "DONE:" << value;
}

void MainTest::exceptRun(const QString& value)
{
    qDebug() << "EXCEPT RUN:" << value;
    throw runtime_error("Hello!");
}

void MainTest::except(const ExecutionException& e,
                      const QString& value)
{
    qDebug() << "Except:" << e.toString() << ":" << value << "cause:" << e.cause().what();
}

void MainTest::simpleTestCase()
{
    using namespace QtPth;
    Thread* th = Thread::spawn(this, this, &MainTest::run, "Main");
    Thread::spawn(th, this, &MainTest::run, "Child-1");
    Thread::spawn(th, this, &MainTest::run, "Child-2");
    Thread::create(th)
            ->except(this, &MainTest::except, "Child-3")
            ->start(this, &MainTest::exceptRun, "Child-3");
    delete th;
}


}
