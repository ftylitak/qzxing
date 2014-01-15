#include <QtGlobal>
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "droparea.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <qdeclarative.h>
#else
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#endif

#include <QZXing.h>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QZXing::registerQMLTypes();

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    qmlRegisterType<DropArea>("DropArea", 1, 0, "DropArea");
    viewer.setMainQmlFile(QLatin1String("qml/QZXingTestApp/main_QtQuick1.qml"));
#else
    QGuiApplication* app = new QGuiApplication(argc, argv);

    QZXing::registerQMLTypes();

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/QZXingTestApp/main_QtQuick2.qml"));
#endif
    viewer.showExpanded();

    return app->exec();
}
