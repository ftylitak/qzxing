#include "application.h"
#include <QDebug>

Application::Application()
{
    //both signals will be connected to the same function for
    //simplicity

    connect(this, &Application::onPermissionsGranted,
            this, &Application::initializeQML);

    connect(this, &Application::onPermissionsDenied,
            this, &Application::initializeQML);
}

void Application::initializeQML()
{
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}

void Application::checkPermissions()
{
    emit onPermissionsGranted();
}
