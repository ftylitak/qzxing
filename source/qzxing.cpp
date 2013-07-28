#include "qzxing.h"

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/DecodeHints.h>
#include "CameraImageWrapper.h"
#include "imagehandler.h"
#include <QTime>

using namespace zxing;

QZXing::QZXing(QObject *parent) : QObject(parent)
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

void QZXing::setDecoder(const uint &hint)
{
    unsigned int newHints = 0;

    if(hint & DecoderFormat_Aztec)
        newHints |= BarcodeFormat::AZTEC;

    if(hint & DecoderFormat_CODABAR)
        newHints |= BarcodeFormat::CODABAR;

    if(hint & DecoderFormat_CODE_39)
        newHints |= BarcodeFormat::CODE_39;

    if(hint & DecoderFormat_CODE_93)
        newHints |= BarcodeFormat::CODE_93;

    if(hint & DecoderFormat_CODE_128)
        newHints |= BarcodeFormat::CODE_128;

    if(hint & DecoderFormat_DATA_MATRIX)
        newHints |= BarcodeFormat::DATA_MATRIX;

    if(hint & DecoderFormat_EAN_8)
        newHints |= BarcodeFormat::EAN_8;

    if(hint & DecoderFormat_EAN_13)
        newHints |= BarcodeFormat::EAN_13;

    if(hint & DecoderFormat_ITF)
        newHints |= BarcodeFormat::ITF;

    if(hint & DecoderFormat_MAXICODE)
        newHints |= BarcodeFormat::MAXICODE;

    if(hint & DecoderFormat_PDF_417)
        newHints |= BarcodeFormat::ITF;

    if(hint & DecoderFormat_QR_CODE)
        newHints |= BarcodeFormat::QR_CODE;

    if(hint & DecoderFormat_RSS_14)
        newHints |= BarcodeFormat::RSS_14;

    if(hint & DecoderFormat_RSS_EXPANDED)
        newHints |= BarcodeFormat::RSS_EXPANDED;

    if(hint & DecoderFormat_UPC_A)
        newHints |= BarcodeFormat::UPC_A;

    if(hint & DecoderFormat_UPC_E)
        newHints |= BarcodeFormat::UPC_E;

    if(hint & DecoderFormat_UPC_EAN_EXTENSION)
        newHints |= BarcodeFormat::UPC_EAN_EXTENSION;

    enabledDecoders = newHints;

    emit enabledFormatsChanged();
}

QString QZXing::decodeImage(QImage image)
{
    QTime t;
    t.start();
    Ref<Result> res;
    emit decodingStarted();

	if(image.isNull())
	{
		emit decodingFinished(false);
		processingTime = -1;
		return "";
	}

    try{
        Ref<LuminanceSource> imageRef(new CameraImageWrapper(image));
        GlobalHistogramBinarizer* binz = new GlobalHistogramBinarizer(imageRef);

        Ref<Binarizer> bz (binz);
        BinaryBitmap* bb = new BinaryBitmap(bz);

        Ref<BinaryBitmap> ref(bb);

        res = ((MultiFormatReader*)decoder)->decode(ref, DecodeHints((int)enabledDecoders));

        QString string = QString(res->getText()->getText().c_str());
        processingTime = t.elapsed();
        emit tagFound(string);
        emit decodingFinished(true);
        return string;
    }
    catch(zxing::Exception& e)
    {
       emit decodingFinished(false);
       processingTime = -1;
       return "";
    }
}

QString QZXing::decodeImageFromFile(QString imageFilePath)
{
	//used to have a check if this image exists
	//but was removed because if the image file path doesn't point to a valid image
	// then the QImage::isNull will return true and the decoding will fail eitherway.
	return decodeImage(QImage(imageFilePath));
}

QString QZXing::decodeImageQML(QObject *item)
{
    return decodeSubImageQML(item);
}

QString QZXing::decodeSubImageQML(QObject* item,
                                  const double offsetX, const double offsetY,
                                  const double width, const double height)
{
    if(item  == NULL)
    {
        emit decodingFinished(false);
        return "";
    }

    QImage img = ((ImageHandler*)imageHandler)->extractQImage(item, offsetX, offsetY, width, height);

    return decodeImage(img);
}

int QZXing::getProcessTimeOfLastDecoding()
{
    return processingTime;
}

uint QZXing::getEnabledFormats() const
{
    return enabledDecoders;
}




