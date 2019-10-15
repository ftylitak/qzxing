#include <QtGlobal>
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <qdeclarative.h>
#else
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#endif
#include "droparea.h"

#include "QZXing.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QZXing::registerQMLTypes();

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    qmlRegisterType<DropArea>("DropArea", 1, 0, "DropArea");
    viewer.setMainQmlFile(QLatin1String("qml/QZXingDragNDropTest/main_QtQuick1.qml"));
#else
    QGuiApplication* app = new QGuiApplication(argc, argv);

    QZXing::registerQMLTypes();

    QtQuick2ApplicationViewer viewer;
    qmlRegisterType<DropArea>("DropArea", 1, 0, "DropArea");
    viewer.setMainQmlFile(QStringLiteral("qml/QZXingDragNDropTest/main_QtQuick2.qml"));
#endif
    viewer.showExpanded();

    return app->exec();
}
