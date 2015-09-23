#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#include <QReadWriteLock>
#include <QHash>
#include <QMetaType>
#include <QVariant>
#include <QStringList>
#include <QDateTime>
#include <memory>
#include <set>
#include <map>

#include "utils.h"

#ifndef QTPTH_DATE_FMT
#   define QTPTH_DATE_FMT "dd.MM.yyyy hh:mm:ss.zzz"
#endif

#if (defined(__GNUC__) || defined(__GNUG__)) && QTPTH_LONGLOG
#   define QTPTH_FUNC __PRETTY_FUNCTION__
#else
#   define QTPTH_FUNC __func__
#endif

#define QTPTH_ASSERT(cond, args...) \
    Q_ASSERT_X(cond, QTPTH_FUNC, Debug::format(args).toAscii().constData())

using namespace std;

namespace QtPth
{

typedef QString (*DumpStringHelperPtr)(const void*);

template<typename T>
QString dumpStringHelper(const T* t)
{
    return t->toString();
}

#define DUCS(S) CleanString(S)

// This wrapper allows to pass any string to format command
// and show it without any quotes
class CleanString : public QString
{
public:
    CleanString();
    CleanString(const QString& aSource);
};


class Debug
{
public:
    Debug();

    // Register toString() method for type as used for printing in QVariant()
    template<class T>
    static void registerType();

    // Base objects convertion methods
    static QString toString(const char* value);
    static QString toString(const QVariant& value);
    static QString toString(const QString& value);
    static QString toString(const CleanString& value);
    static QString toString(const QByteArray& value);
    static QString toString(const QStringList& value);
    static QString toString(int value);
    static QString toString(unsigned int value);
    static QString toString(short int value);
    static QString toString(qlonglong value);
    static QString toString(qulonglong value);
    static QString toString(long value);
    static QString toString(qreal value);
    static QString toString(bool value);
    static QString toString(QObject* object);
    static QString toString(const QDateTime& value);
    static QString toString(const std::string& value);
    static QString toString(const std::exception& value);

    // Shared pointers
    template<class T>
    static QString toString(const QSharedPointer<T>& ptr);

    template<class T>
    static QString toString(const std::shared_ptr<T>& ptr);


    // Pointers
    template<class T>
    static QString toString(T* ptr);

    // Lists convertion
    template<class T>
    static QString toString(const QList<T>& value);

    // Sets convertion
    template<class T>
    static QString toString(const QSet<T>& value);

    // Hash convertion
    template<class K, class V>
    static QString toString(const QHash<K, V>& value);

    // Map convertion
    template<class K, class V>
    static QString toString(const QMap<K, V>& value);

    // Std Sets convertion
    template<class T>
    static QString toString(const set<T>& value);

    // Std Lists convertion
    template<class T>
    static QString toString(const list<T>& value);

    // Std Maps convertion
    template<class K, class V>
    static QString toString(const map<K, V>& value);

    // Custom object convertion using string method
    template<class T>
    static QString toString(const T& value);

    // Format methods
    static QString format(const QString& asFormat);

    template<class T, class ... Args>
    static QString format(const QString& fmt,
                          const T& first,
                          const Args& ... other);

private:
    static QString userVariantToString(const QVariant& vObject);

private:
    static QReadWriteLock stringHelpersLock;
    static QHash<qint32, DumpStringHelperPtr> stringHelpers;
};


template<class K, class V>
QString Debug::toString(const map<K, V>& value)
{
    QStringList list;
    typename map<K, V>::const_iterator it;
    for(it = value.begin(); it != value.end(); ++it)
        list << format("%1: %2", it->first, it->second);
    return QString("SM{%1}").arg(list.join(", "));
}

template<class T>
QString Debug::toString(const list<T>& value)
{
    QStringList list;
    typename QList<T>::const_iterator it;
    for(it = value.begin(); it != value.end(); ++it)
        list.append(toString(*it));
    return QString("S[%1]").arg(list.join(", "));
}

template<class T>
QString Debug::toString(const set<T>& value)
{
    QStringList list;
    typename set<T>::const_iterator it;
    for(it = value.begin(); it != value.end(); ++it)
        list.append(toString(*it));
    return QString("SS{%1}").arg(list.join(", "));
}

template<class T>
QString Debug::toString(const QSharedPointer<T>& ptr)
{
    return ptr.isNull() ? QString("Shared(NULL)") : format("*%1", *ptr);
}

template<class T>
QString Debug::toString(const std::shared_ptr<T>& ptr)
{
    return ptr.get() ? format("*r%1:%2", ptr.use_count(), *ptr)
                      : format("*r%1(NULL)", ptr.use_count());
}

template<class T>
QString Debug::toString(T* ptr)
{
    return ptr ? Debug::format("*%1", *ptr) : QString("NULL");
}

template<class K, class V>
QString Debug::toString(const QMap<K, V>& value)
{
    QStringList list;
    QMapIterator<K, V> it(value);
    while(it.hasNext())
    {
        it.next();
        list << format("%1: %2", it.key(), it.value());
    }
    return QString("M{%1}").arg(list.join(", "));
}

template<class T>
QString Debug::toString(const QSet<T>& value)
{
    QStringList list;
    QSetIterator<T> it(value);
    while(it.hasNext())
        list << toString(it.next());
    return QString("S{%1}").arg(list.join(", "));
}

template<class K, class V>
QString Debug::toString(const QHash<K, V>& value)
{
    QStringList list;
    QHashIterator<K, V> it(value);
    while(it.hasNext())
    {
        it.next();
        list << format("%1: %2", it.key(), it.value());
    }
    return QString("H{%1}").arg(list.join(", "));
}

template<class T>
QString Debug::toString(const QList<T>& value)
{
    QString line = Utils::joinConv<T>(value, ", ", [](T obj) { return toString(obj); });
    return QString("[%1]").arg(line);
}

template<class T>
QString Debug::toString(const T& value)
{
    return dumpStringHelper<T>(&value);
}

template<class T, class ... Args>
QString Debug::format(const QString& fmt,
                      const T& first,
                      const Args& ... other)
{
    return format(fmt.arg(toString(first)), other...);
}

template<class T>
void Debug::registerType()
{
    typedef QString (*CustomHelperPtr)(const T*);
    CustomHelperPtr dumper = dumpStringHelper<T>;
    qint32 typeId = qMetaTypeId<T>();
    QWriteLocker locker(&stringHelpersLock);
    stringHelpers.insert(typeId, reinterpret_cast<DumpStringHelperPtr>(dumper));
}

}

#endif // DEBUGUTILS_H
