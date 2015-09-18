#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <functional>

#include <QObject>
#include <QUuid>
#include <QDebug>
#include <QStringList>
#include <QReadWriteLock>


namespace QtPth
{

using namespace std;

class Utils
{
public:
    union Uid64
    {
        Uid64()
        {
            intData = 0;
            qMemCopy(data, QUuid::createUuid().data4, sizeof(data));
        }
        uchar data[8];
        qulonglong intData;
    };

public:
    Utils();
    static qulonglong gen64bitUid();
    static QByteArray gen64bitHexUid();
    static QByteArray joinByteArraySet(const QSet<QByteArray>& acSet, const QByteArray& aSep);
    static QString joinByteArrayList(const QList<QByteArray>& acList, const QByteArray& aSep,
                                     int anMaxLemgth = 3000);
    static QString strPtr(void* aPtr);
    static QString strPtr(const void* aPtr);
    static QString strObj(QObject* apObject);

    template<class T>
    static QVariantList toVariant(const QList<T>& acList);

    template<class T>
    static QVariantList toVariant(const QList<T>& acList,
                                  std::function<QVariant(T)> vConverter);

    template<class T>
    static QList<T> toList(const QVariant& aVariant);

    template<class T>
    static QString join(const QList<T>& aList, const QString& aSep);

    template<class T>
    static QString joinConv(const QList<T>& aList, const QString& aSep,
                            std::function<QString(T)> vConverter);
    template<class T>
    static void forEach(const QList<T>& acList, std::function<void(const T&)> aFunc);

    template<class T>
    static QObject* obj(const T apSource);
};


template<class T>
QObject* Utils::obj(const T apSource)
{
    return qobject_cast<QObject*>(apSource);
}


template<class T>
void Utils::forEach(const QList<T>& acList,
                    std::function<void (const T&)> aFunc)
{
    std::for_each(acList.begin(), acList.end(), aFunc);
}


template<class T>
QList<T> Utils::toList(const QVariant& aVariant)
{
    QList<T> vcReturn;
    QVariantList vcList = aVariant.toList();
    for(QVariant vItem : vcList)
        vcReturn.append(vItem.value<T>());
    return vcReturn;
}


template<class T>
QVariantList Utils::toVariant(const QList<T>& acList)
{
    QVariantList vcList;
    for(T vItem : acList)
        vcList.append(vItem);
    return vcList;
}


template<class T>
QVariantList Utils::toVariant(const QList<T>& acList,
                              std::function<QVariant(T)> vConverter)
{
    QVariantList vcList;
    for(const T& vItem : acList)
        vcList.append(vConverter(vItem));
    return vcList;
}


template<class T>
QString Utils::join(const QList<T>& aList, const QString& aSep)
{
    return Utils::joinConv<T>(aList, aSep, [](T aObj) {
        return QString(aObj);
    });
}


template<class T>
QString Utils::joinConv(const QList<T>& aList, const QString& aSep,
                        std::function<QString(T)> vConverter)
{
    QStringList vcResultList;
    for(T vItem : aList)
        vcResultList.append(vConverter(vItem));
    return vcResultList.join(aSep);
}


}

#endif // UTILS_H
