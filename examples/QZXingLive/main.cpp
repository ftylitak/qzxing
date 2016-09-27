#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>

#include <qzxing.h>
#include <Qt>
#include "QZXingFilter.h"


#if defined(Q_OS_IOS)
/// Reference for iOS entry point:
/// http://stackoverflow.com/questions/25353686/you-are-creating-qapplication-before-calling-uiapplicationmain-error-on-ios
extern "C" int qtmn(int argc, char **argv)
#else
int main(int argc, char *argv[])
#endif
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<QZXingFilter>("QZXing", 2, 3, "QZXingFilter");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
