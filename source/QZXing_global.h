#ifndef QZXING_GLOBAL_H
#define QZXING_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QZXING_LIBRARY)
#  define QZXINGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QZXINGSHARED_EXPORT Q_DECL_IMPORT
#endif

#if defined(MSVC2008)
    kyguig
#endif

#endif // QZXING_GLOBAL_H
