#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>

#include <Qt>
#include "QZXing.h"
#include "application.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication app(argc, argv);

    QZXing::registerQMLTypes();

    Application customApp;
    customApp.checkPermissions();

    return app.exec();
}
