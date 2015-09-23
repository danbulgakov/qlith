#include "debug.h"

namespace QtPth
{

QHash<qint32, DumpStringHelperPtr> Debug::stringHelpers;
QReadWriteLock Debug::stringHelpersLock;


Debug::Debug()
{
}


QString Debug::userVariantToString(const QVariant& vObject)
{
    QReadLocker locker(&stringHelpersLock);
    qint32 vnType = vObject.userType();
    DumpStringHelperPtr texter = stringHelpers.value(vnType);
    if(texter)
        return texter(vObject.constData());
    return vObject.typeName();
}


QString Debug::toString(const char* value)
{
    return toString(QString::fromAscii(QByteArray(value)));
}


QString Debug::toString(const QVariant& value)
{
    switch(value.type())
    {
    case QVariant::Invalid:
        return "Invalid";
    case QVariant::Map:
        return toString(value.toMap());
    case QVariant::List:
        return toString(value.toList());
    case QVariant::StringList:
        return toString(value.toStringList());
    case QVariant::UserType:
        return Debug::userVariantToString(value);
    case QVariant::String:
        return toString(value.toString());
    case QVariant::DateTime:
        return toString(value.toDateTime());
    default:
        return value.toString();
    }
    return QString();
}


QString Debug::toString(const QString& value)
{
    return QString("\"%1\"").arg(value);
}


QString Debug::toString(const CleanString& value)
{
    return value;
}


QString Debug::toString(const QByteArray& value)
{
    return QString("%1\"%2\"")
            .arg(value.isEmpty() ? "" : QString("#%1").arg(value.size()))
            .arg(QString::fromAscii(value));
}


QString Debug::toString(const QStringList& value)
{
    return toString<QString>(value);
}


QString Debug::toString(int value)
{
    return QString::number(value);
}


QString Debug::toString(unsigned int value)
{
    return QString::number(value);
}


QString Debug::toString(short int value)
{
    return QString::number(value);
}


QString Debug::toString(qlonglong value)
{
    return QString::number(value);
}


QString Debug::toString(qulonglong value)
{
    return QString::number(value);
}


QString Debug::toString(long value)
{
    return QString::number(value);
}


QString Debug::toString(qreal value)
{
    return QString::number(value);
}


QString Debug::toString(bool value)
{
    return value ? "Yes" : "No";
}


QString Debug::toString(QObject* object)
{
    return Utils::strObj(object);
}


QString Debug::toString(const QDateTime& value)
{
    QDateTime vUTC = value.timeSpec() == Qt::LocalTime ? value.toUTC() : value;
    return value.isValid() ? vUTC.toString(QTPTH_DATE_FMT) : QString::fromAscii("Invalid");
}


QString Debug::toString(const std::string& value)
{
    return toString(QString::fromStdString(value));
}


QString Debug::toString(const exception& value)
{
    return QString("SExcept('%1')").arg(value.what());
}


QString Debug::format(const QString& asFormat)
{
    return asFormat;
}


CleanString::CleanString()
{
}


CleanString::CleanString(const QString& aSource) :
    QString(aSource)
{
}

}
