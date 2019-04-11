#include "QZXingPlugin.h"
#include "QZXing.h"
#include <QtQml/qqml.h>
#ifdef QZXING_MULTIMEDIA
#include <QZXingFilter.h>
#endif
#include "QZXingImageProvider.h"

void QZXingPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("QZXing"));
    qmlRegisterType<QZXing>("QZXing", 2, 3, "QZXing");

#ifdef QZXING_MULTIMEDIA
    qmlRegisterType<QZXingFilter>("QZXing", 2, 3, "QZXingFilter");
#endif //QZXING_MULTIMEDIA
    qmlProtectModule(uri, 2);
}

void QZXingPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    engine->addImageProvider(QLatin1String("QZXing"), new QZXingImageProvider());
}
