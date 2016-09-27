#include "QZXingFilter.h"

#include <QDebug>
#include <QtConcurrent/QtConcurrent>

QZXingFilter::QZXingFilter(QObject *parent)
    : QAbstractVideoFilter(parent)
    , decoding(false)
{
    /// By default all the types are enabled but hence that it is extra processing.
    decoder.setDecoder(QZXing::DecoderFormat_Aztec | QZXing::DecoderFormat_QR_CODE);

    /// Conecting signals to handlers that will send signals to QML
    connect(&decoder, &QZXing::decodingStarted,
            this, &QZXingFilter::handleDecodingStarted);
    connect(&decoder, &QZXing::decodingFinished,
            this, &QZXingFilter::handleDecodingFinished);
    connect(&decoder, &QZXing::tagFound,
            this, &QZXingFilter::handleTagFound);
}

QZXingFilter::~QZXingFilter()
{

}

void QZXingFilter::handleDecodingStarted()
{
    decoding = true;
    emit decodingStarted();
    emit isDecodingChanged();
}

void QZXingFilter::handleDecodingFinished(bool succeeded)
{
    decoding = false;
    emit decodingFinished(succeeded, decoder.getProcessTimeOfLastDecoding());
    emit isDecodingChanged();
}

void QZXingFilter::handleTagFound(QString tag)
{
//    qDebug() << "handleTagFound";
    emit tagFound(tag);
}

QVideoFilterRunnable * QZXingFilter::createFilterRunnable()
{
    return new QZXingFilterRunnable(this);
}

/// Qt cant natively create a QImage from certain PixelFormats (BGR and YUV).
/// As Android QVideoFrames are encoded as BGR, we created this conversion function.
QImage QZXingFilter::fromBGRAtoARGB(uchar * data, QSize size, QVideoFrame::PixelFormat pixelFormat)
{
    if(pixelFormat != QVideoFrame::Format_BGRA32
            && pixelFormat != QVideoFrame::Format_BGRA32_Premultiplied
            && pixelFormat != QVideoFrame::Format_BGR32)
    {
        return QImage();
    }

    QImage image(data, size.width(), size.height(), QImage::Format_ARGB32);

    int curPixel = 0;
    unsigned char * pCur = 0;
    unsigned char * pPixel = image.bits();
    for (int i = 0; i < size.width() * size.height(); ++i)
    {
        curPixel = *((int *)pPixel); /// This changes the order of the bytes. Endianness?
        pCur = (unsigned char *)&curPixel;

        /*B*/ pPixel[0] = pCur[0]; // B
        /*G*/ pPixel[1] = pCur[1]; // G
        /*R*/ pPixel[2] = pCur[2]; // R
        /*A*/ pPixel[3] = 0xFF;    // A Channel is ignored.

        pPixel += 4;
    }

    return image;
}

///
/// QZXingFilterRunnable
///

QZXingFilterRunnable::QZXingFilterRunnable(QZXingFilter * filter)
    : QObject(nullptr)
    , filter(filter)
{

}

QVideoFrame QZXingFilterRunnable::run(QVideoFrame * input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{
    Q_UNUSED(surfaceFormat);
    Q_UNUSED(flags);

    /// We dont want to decode every single frame we get, as this would be very costly
    /// These checks are attempt on having only 1 frame being processed at a time.
    if(!input || !input->isValid())
    {
//        qDebug() << "[QZXingFilterRunnable] Invalid Input ";
        return * input;
    }
    if(filter->isDecoding())
    {
//        qDebug() << "------ decoder busy.";
        return * input;
    }
    if(!filter->processThread.isFinished())
    {
//        qDebug() << "--[]-- decoder busy.";
        return * input;
    }

    filter->decoding = true;

    /// Copy the data we need to the filter.
	/// TODO: Depending on the system / platform, this copy hangs up the UI for some seconds. Fix this.
    filter->frame.copyData(* input);

    /// All processing that has to happen in another thread, as we are now in the UI thread.
    filter->processThread = QtConcurrent::run(this, &QZXingFilterRunnable::processVideoFrameProbed, filter->frame);

    return * input;
}

void QZXingFilterRunnable::processVideoFrameProbed(SimpleVideoFrame & videoFrame)
{
    static unsigned int i = 0; i++;
//    qDebug() << "Future: Going to process frame: " << i;

    /// Create QImage from QVideoFrame.
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat);
    QImage image((uchar*)videoFrame.data.data(), videoFrame.size.width(), videoFrame.size.height(), imageFormat);

    /// If it fails, it's probably a format problem.
    /// Let's try to convert it from BGR formats to RGB
    if(image.isNull())
        image = QZXingFilter::fromBGRAtoARGB((uchar*)videoFrame.data.data(), videoFrame.size, videoFrame.pixelFormat);

    /// This is a forced "conversion", colors end up swapped.
    if(image.isNull() && videoFrame.pixelFormat == QVideoFrame::Format_BGR555)
        image = QImage((uchar*)videoFrame.data.data(), videoFrame.size.width(), videoFrame.size.height(), QImage::Format_RGB555);

    /// This is a forced "conversion", colors end up swapped.
    if(image.isNull() && videoFrame.pixelFormat == QVideoFrame::Format_BGR565)
        image = QImage((uchar*)videoFrame.data.data(), videoFrame.size.width(), videoFrame.size.height(), QImage::Format_RGB16);

    /// This is a forced "conversion", colors end up swapped.
    if(image.isNull() && videoFrame.pixelFormat == QVideoFrame::Format_BGR24)
        image = QImage((uchar*)videoFrame.data.data(), videoFrame.size.width(), videoFrame.size.height(), QImage::Format_RGB888);

    /// TODO: Handle (create QImages from) YUV formats.

    if(image.isNull())
    {
        qDebug() << "QZXingFilterRunnable error: Cant create image file to process.";
        qDebug() << "Maybe it was a format conversion problem? ";
        qDebug() << "VideoFrame format: " << videoFrame.pixelFormat;
        qDebug() << "Image corresponding format: " << imageFormat;
        filter->decoding = false;
        return;
    }

    /// The frames we get from the camera may be reflected horizontally or vertically
    /// As the decoder can't handle reflected frames, we swap them in all possible frames, changing the swap mode each frame.
	/// TODO: Maybe there is a better way to know this orientation beforehand? Or should we try decoding all of them?
    switch (i % 4)
    {
        case 0:
            image = image.mirrored(false, false);
        break;
        case 1:
            image = image.mirrored(true, false);
        break;
        case 2:
            image = image.mirrored(false, true);
        break;
        case 3:
            image = image.mirrored(true, true);
        break;
    }

//    qDebug() << "image mirrored type == " << (i % 4);
//    qDebug() << "image.size() " << image.size();
//    qDebug() << "image.format() " << image.format();

//    QString path;
//    path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/qrtest";
//    qDebug() << "saving image " + QString::number(i) + " at:  "
//             << path << image.save(path + "/test_" + QString::number(i) + ".png");

    filter->decoder.decodeImage(image);
}
