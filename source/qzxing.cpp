#include "qzxing.h"

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/DecodeHints.h>
#include "CameraImageWrapper.h"

using namespace zxing;

QZXing::QZXing(QObject *parent) : QObject(parent)
{
    decoder = new MultiFormatReader();
    ((MultiFormatReader*)decoder)->setHints(DecodeHints::DEFAULT_HINT);
}

void QZXing::setDecoder(DecoderFormat hint)
{
    DecodeHints enabledDecoders;

    if(hint & DecoderFormat_QR_CODE)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_QR_CODE);

    if(hint & DecoderFormat_DATA_MATRIX)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_DATA_MATRIX);

    if(hint & DecoderFormat_UPC_E)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_UPC_E);

    if(hint & DecoderFormat_UPC_A)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_UPC_A);

    if(hint & DecoderFormat_EAN_8)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_EAN_8);

    if(hint & DecoderFormat_EAN_13)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_EAN_13);

    if(hint & DecoderFormat_CODE_128)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_CODE_128);

    if(hint & DecoderFormat_CODE_39)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_CODE_39);

    if(hint & DecoderFormat_ITF)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_ITF);

    ((MultiFormatReader*)decoder)->setHints(enabledDecoders);
}

QString QZXing::decodeImage(QImage image)
{
    Ref<Result> res;
    emit decodingStarted();

    try{
        Ref<LuminanceSource> imageRef(new CameraImageWrapper(image));
        GlobalHistogramBinarizer* binz = new GlobalHistogramBinarizer(imageRef);

        Ref<Binarizer> bz (binz);
        BinaryBitmap* bb = new BinaryBitmap(bz);

        Ref<BinaryBitmap> ref(bb);

        res = ((MultiFormatReader*)decoder)->decode(ref);

        QString string = QString(res->getText()->getText().c_str());
        emit tagFound(string);
        emit decodingFinished(true);
        return string;
    }
    catch(zxing::Exception& e)
    {
       emit decodingFinished(false);
       return "";
    }
}
