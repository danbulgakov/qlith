#include "utils.h"
namespace QtPth
{


Utils::Utils()
{
}


qulonglong Utils::gen64bitUid()
{
    Uid64 vResult;
    return vResult.intData;
}


QByteArray Utils::gen64bitHexUid()
{
    return QByteArray::number(gen64bitUid(), 16);
}


QByteArray Utils::joinByteArraySet(const QSet<QByteArray>& acSet,
                                   const QByteArray& aSep)
{
    QByteArray vsResult;
    for(QByteArray vItem : acSet)
    {
        if(!vsResult.isEmpty())
            vsResult += aSep;
        vsResult += vItem;
    }
    return vsResult;
}


QString Utils::joinByteArrayList(const QList<QByteArray>& acList, const QByteArray& aSep,
                                 int anMaxLemgth)
{
    QString vsResult = Utils::joinConv<QByteArray>(acList, aSep, [](QByteArray aObj) {
        return QString(aObj);
    });
    if(vsResult.size() <= anMaxLemgth)
        return vsResult;
    else
    {
        vsResult.truncate(anMaxLemgth);
        return vsResult + "...";
    }
}


QString Utils::strPtr(void* aPtr)
{
    return QString("0x%1").arg(quintptr(aPtr), 0, 16);
}


QString Utils::strPtr(const void* aPtr)
{
    return aPtr ? QString("0x%1").arg(quintptr(aPtr), 0, 16) : "NULL";
}


QString Utils::strObj(const QObject* apObject)
{
    if(apObject)
    {
        return QString("QObject(%1:%2:%3)")
               .arg(apObject->metaObject()->className())
               .arg(apObject->objectName())
               .arg(Utils::strPtr(apObject));
    }
    else
    {
        return QString::fromAscii("QObject(NULL)");
    }
}


}
