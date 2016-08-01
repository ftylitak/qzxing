#include "QZXing.h"

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/DecodeHints.h>
#include "CameraImageWrapper.h"
#include "imagehandler.h"
#include <QTime>
#include <QUrl>
#include <zxing/qrcode/encoder/Encoder.h>
#include <zxing/qrcode/ErrorCorrectionLevel.h>
#include <QColor>

using namespace zxing;

QZXing::QZXing(QObject *parent) : QObject(parent), tryHarder_(false)
{
    decoder = new MultiFormatReader();
    /*setDecoder(DecoderFormat_QR_CODE |
               DecoderFormat_DATA_MATRIX |
               DecoderFormat_UPC_E |
               DecoderFormat_UPC_A |
               DecoderFormat_EAN_8 |
               DecoderFormat_EAN_13 |
               DecoderFormat_CODE_128 |
               DecoderFormat_CODE_39 |
               DecoderFormat_ITF |
               DecoderFormat_Aztec);*/
    imageHandler = new ImageHandler();
}

QZXing::~QZXing()
{
    if (imageHandler)
        delete imageHandler;

    if (decoder)
        delete decoder;
}

QZXing::QZXing(QZXing::DecoderFormat decodeHints, QObject *parent) : QObject(parent)
{
    decoder = new MultiFormatReader();
    imageHandler = new ImageHandler();

    setDecoder(decodeHints);
}

void QZXing::setTryHarder(bool tryHarder)
{
    tryHarder_ = tryHarder;
}

bool QZXing::getTryHarder()
{
    return tryHarder_;
}

QString QZXing::decoderFormatToString(int fmt)
{
    switch (fmt) {
    case DecoderFormat_Aztec:
        return "AZTEC";

    case DecoderFormat_CODABAR:
        return "CODABAR";

    case DecoderFormat_CODE_39:
        return "CODE_39";

    case DecoderFormat_CODE_93:
        return "CODE_93";

    case DecoderFormat_CODE_128:
        return "CODE_128";

    case DecoderFormat_DATA_MATRIX:
        return "DATA_MATRIX";

    case DecoderFormat_EAN_8:
        return "EAN_8";

    case DecoderFormat_EAN_13:
        return "EAN_13";

    case DecoderFormat_ITF:
        return "ITF";

    case DecoderFormat_MAXICODE:
        return "MAXICODE";

    case DecoderFormat_PDF_417:
        return "PDF_417";

    case DecoderFormat_QR_CODE:
        return "QR_CODE";

    case DecoderFormat_RSS_14:
        return "RSS_14";

    case DecoderFormat_RSS_EXPANDED:
        return "RSS_EXPANDED";

    case DecoderFormat_UPC_A:
        return "UPC_A";

    case DecoderFormat_UPC_E:
        return "UPC_E";

    case DecoderFormat_UPC_EAN_EXTENSION:
        return "UPC_EAN_EXTENSION";
    } // switch
    return QString();
}

QString QZXing::foundedFormat() const
{
    return foundedFmt;
}

QString QZXing::charSet() const
{
    return charSet_;
}

void QZXing::setDecoder(const uint &hint)
{
    unsigned int newHints = 0;

    if(hint & DecoderFormat_Aztec)
        newHints |= DecodeHints::AZTEC_HINT;

    if(hint & DecoderFormat_CODABAR)
        newHints |= DecodeHints::CODABAR_HINT;

    if(hint & DecoderFormat_CODE_39)
        newHints |= DecodeHints::CODE_39_HINT;

    if(hint & DecoderFormat_CODE_93)
        newHints |= DecodeHints::CODE_93_HINT;

    if(hint & DecoderFormat_CODE_128)
        newHints |= DecodeHints::CODE_128_HINT;

    if(hint & DecoderFormat_DATA_MATRIX)
        newHints |= DecodeHints::DATA_MATRIX_HINT;

    if(hint & DecoderFormat_EAN_8)
        newHints |= DecodeHints::EAN_8_HINT;

    if(hint & DecoderFormat_EAN_13)
        newHints |= DecodeHints::EAN_13_HINT;

    if(hint & DecoderFormat_ITF)
        newHints |= DecodeHints::ITF_HINT;

    if(hint & DecoderFormat_MAXICODE)
        newHints |= DecodeHints::MAXICODE_HINT;

    if(hint & DecoderFormat_PDF_417)
        newHints |= DecodeHints::PDF_417_HINT;

    if(hint & DecoderFormat_QR_CODE)
        newHints |= DecodeHints::QR_CODE_HINT;

    if(hint & DecoderFormat_RSS_14)
        newHints |= DecodeHints::RSS_14_HINT;

    if(hint & DecoderFormat_RSS_EXPANDED)
        newHints |= DecodeHints::RSS_EXPANDED_HINT;

    if(hint & DecoderFormat_UPC_A)
        newHints |= DecodeHints::UPC_A_HINT;

    if(hint & DecoderFormat_UPC_E)
        newHints |= DecodeHints::UPC_E_HINT;

    if(hint & DecoderFormat_UPC_EAN_EXTENSION)
        newHints |= DecodeHints::UPC_EAN_EXTENSION_HINT;

    enabledDecoders = newHints;

    emit enabledFormatsChanged();
}

QString QZXing::decodeImage(const QImage &image, int maxWidth, int maxHeight, bool smoothTransformation)
{
    QTime t;
    t.start();
    Ref<Result> res;
    emit decodingStarted();

    if(image.isNull())
    {
        emit decodingFinished(false);
        processingTime = t.elapsed();
        return "";
    }

    CameraImageWrapper *ciw = NULL;

    if ((maxWidth > 0) || (maxHeight > 0))
        ciw = CameraImageWrapper::Factory(image, maxWidth, maxHeight, smoothTransformation);
    else
        ciw = CameraImageWrapper::Factory(image, 999, 999, true);

    QString errorMessage = "Unknown";
    try {
        Ref<LuminanceSource> imageRef(ciw);
        Ref<GlobalHistogramBinarizer> binz( new GlobalHistogramBinarizer(imageRef) );
        Ref<BinaryBitmap> bb( new BinaryBitmap(binz) );

        DecodeHints hints((int)enabledDecoders);

        bool hasSucceded = false;
        try {
            res = decoder->decode(bb, hints);
            hasSucceded = true;
        }catch(zxing::Exception &e){}

        if(!hasSucceded)
        {
            hints.setTryHarder(true);

            try {
                res = decoder->decode(bb, hints);
                hasSucceded = true;
            } catch(zxing::Exception &e) {}

            if (tryHarder_ && bb->isRotateSupported()) {
                Ref<BinaryBitmap> bbTmp = bb;

                for (int i=0; (i<3 && !hasSucceded); i++) {
                    Ref<BinaryBitmap> rotatedImage(bbTmp->rotateCounterClockwise());
                    bbTmp = rotatedImage;

                    try {
                        res = decoder->decode(rotatedImage, hints);
                        hasSucceded = true;
                    } catch(zxing::Exception &e) {}
                }
            }
        }

        if (hasSucceded) {
            QString string = QString(res->getText()->getText().c_str());
            if (!string.isEmpty() && (string.length() > 0)) {
                int fmt = res->getBarcodeFormat().value;
                foundedFmt = decoderFormatToString(fmt);
                charSet_ = QString::fromStdString(res->getCharSet());
                if (!charSet_.isEmpty()) {
                    QTextCodec *codec = QTextCodec::codecForName(res->getCharSet().c_str());
                    if (codec)
                        string = codec->toUnicode(res->getText()->getText().c_str());
                }
                emit tagFound(string);
                emit tagFoundAdvanced(string, foundedFmt, charSet_);
            }
            processingTime = t.elapsed();
            emit decodingFinished(true);
            return string;
        }
    }
    catch(zxing::Exception &e)
    {
        errorMessage = QString(e.what());
    }

    emit error(errorMessage);
    emit decodingFinished(false);
    processingTime = t.elapsed();
    return "";
}

QString QZXing::decodeImageFromFile(const QString& imageFilePath, int maxWidth, int maxHeight, bool smoothTransformation)
{
    // used to have a check if this image exists
    // but was removed because if the image file path doesn't point to a valid image
    // then the QImage::isNull will return true and the decoding will fail eitherway.
    const QString header = "file://";

    QString filePath = imageFilePath;
    if(imageFilePath.startsWith(header))
        filePath = imageFilePath.right(imageFilePath.size() - header.size());

    QUrl imageUrl = QUrl::fromLocalFile(filePath);
    QImage tmpImage = QImage(imageUrl.toLocalFile());
    return decodeImage(tmpImage, maxWidth, maxHeight, smoothTransformation);
}

QString QZXing::decodeImageQML(QObject *item)
{
    return decodeSubImageQML(item);
}

QString QZXing::decodeSubImageQML(QObject *item,
                                  const double offsetX, const double offsetY,
                                  const double width, const double height)
{
    if(item  == NULL)
    {
        processingTime = 0;
        emit decodingFinished(false);
        return "";
    }

    QImage img = imageHandler->extractQImage(item, offsetX, offsetY, width, height);

    return decodeImage(img);
}

QString QZXing::decodeImageQML(const QUrl &imageUrl)
{
    return decodeSubImageQML(imageUrl);
}

QString QZXing::decodeSubImageQML(const QUrl &imageUrl,
                                  const double offsetX, const double offsetY,
                                  const double width, const double height)
{
    QString imagePath = imageUrl.path();
    imagePath = imagePath.trimmed();
    QFile file(imagePath);
    if (!file.exists()) {
        qDebug() << "[decodeSubImageQML()] The file" << file.fileName() << "does not exist.";
        emit decodingFinished(false);
        return "";
    }
    QImage img(imageUrl.path());
    if(!(offsetX == 0 && offsetY == 0 && width == 0 && height == 0)) {
        img = img.copy(offsetX, offsetY, width, height);
    }
    return decodeImage(img);
}

QImage QZXing::encodeData(const QString& data)
{
    QImage image;
    try {
        Ref<qrcode::QRCode> barcode = qrcode::Encoder::encode(data, qrcode::ErrorCorrectionLevel::L );
        Ref<qrcode::ByteMatrix> bytesRef = barcode->getMatrix();
        const std::vector< std::vector <zxing::byte> >& bytes = bytesRef->getArray();
        image = QImage(bytesRef->getWidth(), bytesRef->getHeight(), QImage::Format_ARGB32);
        for(int i=0; i<bytesRef->getWidth(); i++)
            for(int j=0; j<bytesRef->getHeight(); j++)
                image.setPixel(i, j, bytes[i][j] ?
                                   qRgb(0,0,0) :
                                   qRgb(255,255,255));

        image = image.scaled(240, 240);
        QZXingImageProvider::getInstance()->storeImage(image);
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return image;
}

int QZXing::getProcessTimeOfLastDecoding()
{
    return processingTime;
}

uint QZXing::getEnabledFormats() const
{
    return enabledDecoders;
}
