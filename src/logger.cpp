#include "logger.h"
namespace QtPth
{

QString Logger::priority(Logger::Priority priority)
{
    switch(priority)
    {
    case QtPth::Logger::DEBUG:
        return "DEBUG";
    case QtPth::Logger::INFO:
        return "INFO";
    case QtPth::Logger::NOTICE:
        return "NOTICE";
    case QtPth::Logger::WARNING:
        return "WARNING";
    case QtPth::Logger::ERROR:
        return "ERROR";
    }
    return "UNKNWON";
}


void Logger::post(Logger::Priority priority,
                  const QString& category,
                  const QString& sender,
                  const QString& text)
{
    for(const HandlerFunc& handler: mHandlers)
    {
        handler(priority, category, sender, text);
    }
}

Logger::Logger()
{
}

Logger::~Logger()
{
}

Logger* Logger::instance()
{
    if(_instance == 0)
    {
        _instance = new Logger();
    }
    return _instance;
}

void Logger::free()
{
    if(_instance)
    {
        delete _instance;
        _instance = NULL;
    }
}

void Logger::addHandler(HandlerFunc handler)
{
    mHandlers.append(handler);
}


Logger* Logger::_instance = 0;
bool Logger::_removed = false;

}
