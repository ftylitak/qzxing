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

#include <QDebug>

using namespace zxing;

QZXingWorker_p::QZXingWorker_p(QObject *parent) :
    QObject(parent), maxWidth(-1), maxHeight(-1), smoothTransformation(false)
{
}

QString QZXingWorker_p::decode()
{
    qDebug() << "Entered threaded decoding";
    QTime t;
    t.start();
    Ref<Result> res;
    emit decodingStarted();

    if(image.isNull())
    {
        emit decodingFinished(false);

        //*processingTime = -1;

        qDebug() << "Exited threaded decoding, error";

        emit quitThread();
        return "";
    }

    try{
        CameraImageWrapper ciw;

        ciw.setSmoothTransformation(smoothTransformation);
        ciw.setImage(image, maxWidth, maxHeight);

        Ref<LuminanceSource> imageRef(&ciw);
        GlobalHistogramBinarizer binz(imageRef);

        Ref<Binarizer> bz (&binz);
        BinaryBitmap bb(bz);

        Ref<BinaryBitmap> ref(&bb);

        res = ((MultiFormatReader*)decoder)->decode(ref, DecodeHints((int)enabledDecoders));

        QString string = QString(res->getText()->getText().c_str());
       // *processingTime = t.elapsed();
        emit tagFound(string);
        emit decodingFinished(true);

        qDebug() << "Exited threaded decoding";
        emit quitThread();
        return string;
    }
    catch(zxing::Exception& e)
    {
       emit decodingFinished(false);
      // *processingTime = -1;

        qDebug() << "Exited threaded decoding, error";
        emit quitThread();
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
