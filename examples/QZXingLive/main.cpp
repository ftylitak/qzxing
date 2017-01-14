#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>

#include <Qt>
#include "QZXingFilter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<QZXingFilter>("QZXing", 2, 3, "QZXingFilter");
    qmlRegisterType<QZXing>("QZXing", 2, 3, "QZXing");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
