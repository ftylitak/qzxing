#include "application.h"
#include <QDebug>
#include "native.h"

#if defined(Q_OS_ANDROID)
    #include <QAndroidJniObject>
    #include <QtAndroid>
#endif // Q_OS_ANDROID

Application::Application()
{
    //both signals will be connected to the same function for
    //simplicity

    connect(this, &Application::onPermissionsGranted,
            this, &Application::initializeQML);

    connect(this, &Application::onPermissionsDenied,
            this, &Application::initializeQML);

    NativeHelpers::registerApplicationInstance(this);
}

void Application::initializeQML()
{
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
}

void Application::checkPermissions()
{
#if defined(Q_OS_ANDROID)
    //intentionally called in the C++ thread since it is blocking and will continue after the check
    qDebug() << "About to request permissions";

        QAndroidJniObject::callStaticMethod<void>("org/ftylitak/qzxing/Utilities",
                                        "requestQZXingPermissions",
                                        "(Landroid/app/Activity;)V",
                                        QtAndroid::androidActivity().object());
    qDebug() << "Permissions granted";
#else
    emit onPermissionsGranted();
#endif //Q_OS_ANDROID
}
