#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QZXing.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QZXing::registerQMLTypes();
    QtQuick2ApplicationViewer viewer;

    QZXing::registerQMLImageProvider(viewer);
    viewer.setMainQmlFile(QStringLiteral("qml/BarcodeEncoder/main.qml"));

    viewer.showExpanded();

    return app.exec();
}
