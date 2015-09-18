#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(QTSHAREDLIB_LIBRARY)
    #define QTSHAREDLIB_EXPORT Q_DECL_EXPORT
#else
    #define QTSHAREDLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBAL_H

