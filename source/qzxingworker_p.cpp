#include "qzxingworker_p.h"

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/DecodeHints.h>
#include "CameraImageWrapper.h"
#include "imagehandler.h"
#include <QTime>
#include <qzxing.h>

using namespace zxing;

QZXingWorker_p::QZXingWorker_p(QObject *parent) :
    QObject(parent)
{
}

QString QZXingWorker_p::decode()
{
    QTime t;
    t.start();
    Ref<Result> res;
    emit decodingStarted();

    if(image.isNull())
    {
        emit decodingFinished(false);
        *processingTime = -1;
        return "";
    }

    try{
        CameraImageWrapper* ciw;

        if(maxWidth > 0 || maxHeight > 0)
        {
            ciw = new CameraImageWrapper();
            ciw->setSmoothTransformation(smoothTransformation);
            ciw->setImage(image, maxWidth, maxHeight);
        }
        else
            ciw = new CameraImageWrapper(image);

        Ref<LuminanceSource> imageRef(ciw);
        GlobalHistogramBinarizer* binz = new GlobalHistogramBinarizer(imageRef);

        Ref<Binarizer> bz (binz);
        BinaryBitmap* bb = new BinaryBitmap(bz);

        Ref<BinaryBitmap> ref(bb);

        res = ((MultiFormatReader*)decoder)->decode(ref, DecodeHints((int)enabledDecoders));

        QString string = QString(res->getText()->getText().c_str());
        *processingTime = t.elapsed();
        emit tagFound(string);
        emit decodingFinished(true);

        delete ciw;
        delete binz;
        delete bb;

        return string;
    }
    catch(zxing::Exception& e)
    {
       emit decodingFinished(false);
       *processingTime = -1;
       return "";
    }
}

void QZXingWorker_p::setData(int *processingTime, QImage image, int maxWidth, int maxHeight, bool smoothTransformation, void *decoder, uint enabledDecoders)
{
    this->processingTime = processingTime;
    this->image = image;
    this->maxWidth = maxWidth;
    this->maxHeight = maxHeight;
    this->smoothTransformation = smoothTransformation;
    this->decoder = decoder;
    this->enabledDecoders = enabledDecoders;
}
