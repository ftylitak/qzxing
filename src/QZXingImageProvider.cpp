#include "QZXingImageProvider.h"
#include <QZXing>

QZXingImageProvider::QZXingImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QImage QZXingImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int slashIndex = id.indexOf('/');
    if (slashIndex == -1) {
        qWarning() << "Can't parse url" << id << ". Usage is <format>/<data>";
        return QImage();
    }

    QUrl formatUrl = id.left(slashIndex);
    QString encodeFormat = formatUrl.path();
    if (encodeFormat != "qrcode") {
        qWarning() << "Encoding format" << encodeFormat << "is not supported. Only qrcode is supported";
        return QImage();
    }

    QList<QPair<QString, QString>> encodeOptions = QUrlQuery(formatUrl).queryItems();
    Q_UNUSED(encodeOptions)

    QString data = id.mid(slashIndex + 1);

    QImage result = QZXing::encodeData(data);
    *size = result.size();
    return result;
}
