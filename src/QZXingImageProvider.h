#ifndef QZXINGIMAGEPROVIDER_H
#define QZXINGIMAGEPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>
#include <QImage>

class QZXingImageProvider : public QQuickImageProvider
{
private:
    QPixmap storedPixmap;
    static QZXingImageProvider *singletonInstance_ptr_;
protected:
    QZXingImageProvider();
public:
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    void storeImage(const QImage& providedImage);

    static QZXingImageProvider* getInstance();
};

#endif // QZXINGIMAGEPROVIDER_H
