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

    int customSettingsIndex = id.lastIndexOf('?');

    QString data;
    QImage result;
    QString corretionLevel;
    QString format;
    QZXing::EncodeErrorCorrectionLevel correctionLevelEnum =
            QZXing::EncodeErrorCorrectionLevel_L;

    if(customSettingsIndex >= 0)
    {
        int startOfDataIndex = slashIndex + 1;
        data = id.mid(startOfDataIndex, customSettingsIndex - (startOfDataIndex));

        //The dummy option has been added due to a bug(?) of QUrlQuery
        // it could not recognize the first key-value pair provided
        QUrlQuery optionQuery("options?dummy=&" + id.mid(customSettingsIndex + 1));

        corretionLevel = optionQuery.queryItemValue("corretionLevel");
        format = optionQuery.queryItemValue("format");

        if(corretionLevel == "H")
            correctionLevelEnum = QZXing::EncodeErrorCorrectionLevel_H;
        else if(corretionLevel == "Q")
            correctionLevelEnum = QZXing::EncodeErrorCorrectionLevel_Q;
        else if(corretionLevel == "M")
            correctionLevelEnum = QZXing::EncodeErrorCorrectionLevel_M;
        else if(corretionLevel == "L")
            correctionLevelEnum = QZXing::EncodeErrorCorrectionLevel_L;
    }

    if(!corretionLevel.isEmpty() || !format.isEmpty())
    {
        if(format != "qrcode")
        {
            qWarning() << "Format not supported: " << format;
            return QImage();
        }

        result = QZXing::encodeData(data, QZXing::EncoderFormat_QR_CODE,
                                            requestedSize,
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
