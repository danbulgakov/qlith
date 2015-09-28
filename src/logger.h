#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDir>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QString>
#include <map>

#include "utils.h"
#include "debug.h"

#define CLSIDY QString(QLITH_FUNC)
#define CFIDY QString("%1:0x%2").arg(CLSIDY).arg(quintptr(this), 0, 16, QChar('0'))

#define LG QLith::Logger::instance()

#define DECLARE_LOG_CAT(CAT) static constexpr const char* _logCategory = #CAT

#define ELOG(args...) LG->post(QLith::Logger::ERROR, _logCategory, CFIDY, QLith::Debug::format(args))

#if LOG_LEVEL > 0
    #define WLOG(args...) LG->post(QLith::Logger::WARNING, _logCategory, CFIDY, Debug::format(args))
#else
    #define WLOG(args...) /**/
#endif

#if LOG_LEVEL > 1
    #define NLOG(args...) LG->post(QLith::Logger::NOTICE, _logCategory, CFIDY, Debug::format(args))
#else
    #define NLOG(args...) /**/
#endif

#if LOG_LEVEL > 2
    #define ILOG(args...) LG->post(QLith::Logger::INFO, _logCategory, CFIDY, Debug::format(args))
#else
    #define ILOG(args...) /**/
#endif

#if LOG_LEVEL > 3
    #define DLOG(args...) LG->post(QLith::Logger::DEBUG, _logCategory, CFIDY, Debug::format(args))
#else
    #define DLOG(args...) /**/
#endif


using namespace std;

namespace QLith
{


class Logger
{
public:
    enum Priority
    {
        DEBUG,
        INFO,
        NOTICE,
        WARNING,
        ERROR
    };

    static QString priority(Priority priority);

    typedef function<void(Priority, QString, QString, QString)> HandlerFunc;

public:
    void post(Priority priority,
              const QString& category,
              const QString& sender,
              const QString& text);

    void addHandler(HandlerFunc handler);

private:
    Logger();
    ~Logger();

public:
    static void free();
    static Logger* instance();

private:
    static Logger* _instance;
    static bool _removed;
    QList<HandlerFunc> mHandlers;
};

}
#endif // LOGGER_H
