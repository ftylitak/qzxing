#ifndef APPLICATION_H
#define APPLICATION_H

#include <QQmlApplicationEngine>
#include <QObject>

class Application : public QObject
{
    Q_OBJECT

public:
    Application();

    void checkPermissions();

public slots:
    void initializeQML();

signals:
    void onPermissionsGranted();
    void onPermissionsDenied();

private:
    QQmlApplicationEngine engine;
};

#endif // APPLICATION_H
