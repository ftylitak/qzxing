#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>

#include <Qt>
#include <QZXing.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QZXing::registerQMLTypes();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
