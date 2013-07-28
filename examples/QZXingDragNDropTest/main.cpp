#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <qdeclarative.h>
#include "droparea.h"
#include <QZXing.h>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QZXing::registerQMLTypes();

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    qmlRegisterType<DropArea>("DropArea", 1, 0, "DropArea");
    viewer.setMainQmlFile(QLatin1String("qml/QZXingTestApp/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
