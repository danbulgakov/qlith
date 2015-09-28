#include "maintest.h"
namespace QLith
{

MainTest::MainTest(QObject *parent) : QObject(parent)
{
    LG->addHandler(&QLith::MainTest::logHandler);
    QLith::init();
}


void QLith::MainTest::logHandler(Logger::Priority priority,
                                 const QString& category,
                                 const QString& sender,
                                 const QString& text)
{
    qDebug() << sender << "==>" << text;
}


MainTest::~MainTest()
{
    QLith::free();
}


void MainTest::run(const QString& value)
{
    RunEntity vEntity;
    vEntity.method = "run";
    vEntity.value = value;
    mRuns.append(vEntity);
}


void MainTest::yieldRun(const QString& value)
{
    DLOG("Yield: %1", Thread::current());
    Thread::yield();
    RunEntity vEntity;
    vEntity.method = "yield";
    vEntity.value = value;
    mRuns.append(vEntity);
}


void MainTest::loop(const QString& value)
{
    for(int i = 0; i < 10; ++i)
    {
        RunEntity vEntity;
        vEntity.method = "loop";
        vEntity.value = value;
        mRuns.append(vEntity);
        Thread::sleep(0.01);
    }
}

void MainTest::exceptRun(const QString& value)
{
    RunEntity vEntity;
    vEntity.method = "except-run";
    vEntity.value = value;
    mRuns.append(vEntity);
    throw runtime_error("runtime");
}

void MainTest::except(const ExecutionException& e,
                      const QString& value)
{
    RunEntity vEntity;
    vEntity.method = "except";
    vEntity.value = value;
    mRuns.append(vEntity);
}

void MainTest::simpleYieldTestCase()
{
    mRuns.clear();
    Thread* th = Thread::spawn(this, this, &MainTest::run, "main");
    Thread::spawn(th, this, &MainTest::yieldRun, "child-1");
    Thread::spawn(th, this, &MainTest::run, "child-2");
    delete th;
    QLITH_VERIFYEQ(3, mRuns.size());
    QLITH_VERIFYEQ("run", mRuns[0].method);
    QLITH_VERIFYEQ("main", mRuns[0].value);
    QLITH_VERIFYEQ("run", mRuns[1].method);
    QLITH_VERIFYEQ("child-2", mRuns[1].value);
    QLITH_VERIFYEQ("yield", mRuns[2].method);
    QLITH_VERIFYEQ("child-1", mRuns[2].value);
}

void MainTest::loopExitTestCase()
{
    mRuns.clear();
    Thread* loop = Thread::spawn(this, this, &MainTest::loop, "main");
    Thread::sleep(0.015);
    loop->kill();
    delete loop;
    DLOG(Debug::toString(mRuns));
}

void MainTest::exceptionTestCase()
{
    Thread* th = Thread::spawn(this, this, &MainTest::run, "main");
    Thread::create(th)
            ->except(this, &MainTest::except, "child-3")
            ->start(this, &MainTest::exceptRun, "child-3");
}


}
