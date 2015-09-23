#ifndef TESTUTILS_H
#define TESTUTILS_H

#define QTPTH_VERIFYEQ(expected, actual) \
    QVERIFY2(expected == actual, QString("\nExpected:\n%1\n\nActual:\n%2\n") \
             .arg(Debug::toString(expected)) \
             .arg(Debug::toString(actual)).toAscii().constData())

namespace QtPth
{

class TestUtils
{
public:
    TestUtils();
};

}
#endif // TESTUTILS_H
