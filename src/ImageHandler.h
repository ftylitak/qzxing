#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QObject>
#include <QImage>
#if QT_VERSION >= 0x050000
#include <QSet>
#include <QReadWriteLock>
#endif

class ImageHandler : public QObject
{
    Q_OBJECT
public:
    explicit ImageHandler(QObject *parent = 0);

    QImage extractQImage(QObject *imageObj,
                         int offsetX = 0, int offsetY = 0,
                         int width = 0, int height = 0);

public slots:
    void save(QObject *item, const QString &path,
              const int offsetX = 0, const int offsetY = 0,
              const int width = 0, const int height = 0);
private:
#if QT_VERSION >= 0x050000
    void imageGrabberReady();
    QSet<QObject *> pendingGrabbers;
    QReadWriteLock pendingGrabbersLocker;
#endif
};

#endif // IMAGEHANDLER_H
