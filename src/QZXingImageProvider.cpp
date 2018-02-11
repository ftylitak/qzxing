#include "QZXingImageProvider.h"
#include <QDebug>
#include <QUrlQuery>
#include "QZXing.h"

QZXingImageProvider::QZXingImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QImage QZXingImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int slashIndex = id.indexOf('/');
    if (slashIndex == -1) {
        qWarning() << "Can't parse url" << id << ". Usage is encode?<format>/<data>";
        return QImage();
    }

    //Detect operation (ex. encode)
    QString operationName = id.left(slashIndex);
    if(operationName != "encode")
    {
        qWarning() << "Operation not supported: " << operationName;
        return QImage();
    }

    int optionAreaIndex = id.lastIndexOf('?');

    QString data;
    QImage result;
    if(optionAreaIndex >= 0)
    {
        int startOfDataIndex = slashIndex + 1;
        data = id.mid(startOfDataIndex, optionAreaIndex - (startOfDataIndex));

        //The dummy option has been added due to a bug(?) of QUrlQuery
        // it could not recognize the first key-value pair provided
        QUrlQuery optionQuery("options?dummy=&" + id.mid(optionAreaIndex + 1));

        QString width = optionQuery.queryItemValue("width");
        QString height = optionQuery.queryItemValue("height");
        QString corretionLevel = optionQuery.queryItemValue("corretionLevel");
        QString format = optionQuery.queryItemValue("format");

        if(format != "qrcode")
        {
            qWarning() << "Format not supported: " << format;
            return QImage();
        }

        if(height.isEmpty() && !width.isEmpty())
            height = width;

        if(width.isEmpty() && height.isEmpty())
            width = height;

        QZXing::EncodeErrorCorrectionLevel correctionLevelEnum;
        if(corretionLevel == "H")
            correctionLevelEnum = QZXing::EncodeErrorCorrectionLevel_H;
        else if(corretionLevel == "Q")
            correctionLevelEnum = QZXing::EncodeErrorCorrectionLevel_Q;
        else if(corretionLevel == "M")
            correctionLevelEnum = QZXing::EncodeErrorCorrectionLevel_M;
        else
            correctionLevelEnum = QZXing::EncodeErrorCorrectionLevel_L;

        result = QZXing::encodeData(data, QZXing::EncoderFormat_QR_CODE,
                                    QSize(width.toInt(), height.toInt()),
                                    correctionLevelEnum);
    }
    else
    {
        data = id.mid(slashIndex + 1);
        result = QZXing::encodeData(data);
    }

    *size = result.size();
    return result;
}
