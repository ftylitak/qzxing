#include "QZXingFilter.h"

#include <QDebug>
#include <QtConcurrent/QtConcurrent>

namespace {
    uchar gray(uchar r, uchar g, uchar b)
    {
        return (306 * (r & 0xFF) +
                601 * (g & 0xFF) +
                117 * (b & 0xFF) +
                0x200) >> 10;
    }
    uchar yuvToGray(uchar Y, uchar U, uchar V)
    {
        const int C = (int) Y - 16;
        const int D = (int) U - 128;
        const int E = (int) V - 128;
        return gray(
            qBound(0, (298 * C + 409 * E + 128) >> 8, 255),
            qBound(0, (298 * C - 100 * D - 208 * E + 128) >> 8, 255),
            qBound(0, (298 * C + 516 * D + 128) >> 8, 255)
        );
    }
}

QZXingFilter::QZXingFilter(QObject *parent)
    : QAbstractVideoFilter(parent)
    , decoding(false)
{
    /// Conecting signals to handlers that will send signals to QML
    connect(&decoder, &QZXing::decodingStarted,
            this, &QZXingFilter::handleDecodingStarted);
    connect(&decoder, &QZXing::decodingFinished,
            this, &QZXingFilter::handleDecodingFinished);
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

QVideoFilterRunnable * QZXingFilter::createFilterRunnable()
{
    return new QZXingFilterRunnable(this);
}

/// Qt cant natively create a QImage from certain PixelFormats (BGR and YUV).
/// As Android QVideoFrames are encoded as BGR, we created this conversion function.
QImage QZXingFilter::fromBGRAtoARGB(const uchar * data, QSize size, QVideoFrame::PixelFormat pixelFormat)
{
    if(pixelFormat != QVideoFrame::Format_BGRA32
            && pixelFormat != QVideoFrame::Format_BGRA32_Premultiplied
            && pixelFormat != QVideoFrame::Format_BGR32)
    {
        return QImage();
    }

    QImage image(size.width(), size.height(), QImage::Format_Grayscale8);

    uchar* out = image.bits();
    const int bits = size.width() * size.height();
    for (int i = 0; i < bits; ++i)
    {
        *out = gray(data[2], data[1], data[0]);
        // alpha is ignored
        data += 4;
        ++out;
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
    filter->processThread = QtConcurrent::run(this, &QZXingFilterRunnable::processVideoFrameProbed, filter->frame, filter->captureRect.toRect());

    return * input;
}

void QZXingFilterRunnable::processVideoFrameProbed(SimpleVideoFrame & videoFrame, const QRect& captureRect)
{
    static unsigned int i = 0; i++;
//    qDebug() << "Future: Going to process frame: " << i;

    const int width = videoFrame.size.width();
    const int height = videoFrame.size.height();
    const uchar* data = (uchar*) videoFrame.data.constData();
    /// Create QImage from QVideoFrame.
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat);
    QImage image(data, width, height, imageFormat);

    /// If it fails, it's probably a format problem.
    /// Let's try to convert it from BGR formats to RGB
    if(image.isNull())
        image = QZXingFilter::fromBGRAtoARGB(data, videoFrame.size, videoFrame.pixelFormat);

    /// This is a forced "conversion", colors end up swapped.
    if(image.isNull() && videoFrame.pixelFormat == QVideoFrame::Format_BGR555)
        image = QImage(data, width, height, QImage::Format_RGB555);

    /// This is a forced "conversion", colors end up swapped.
    if(image.isNull() && videoFrame.pixelFormat == QVideoFrame::Format_BGR565)
        image = QImage(data, width, height, QImage::Format_RGB16);

    /// This is a forced "conversion", colors end up swapped.
    if(image.isNull() && videoFrame.pixelFormat == QVideoFrame::Format_BGR24)
        image = QImage(data, width, height, QImage::Format_RGB888);

    //fix for issues #4 and #9
    if(image.isNull() && videoFrame.pixelFormat == QVideoFrame::Format_YUV420P) {
        image = QImage(videoFrame.size, QImage::Format_Grayscale8);
        uchar* pixel = image.bits();
        const int wh = width * height;
        const int w_2 = width / 2;
        const int wh_54 = wh * 5 / 4;
        for (int y = 0; y < height; y++) {
            const int Y_offset = y * width;
            const int y_2 = y / 2;
            const int U_offset = y_2 * w_2 + wh;
            const int V_offset = y_2 * w_2 + wh_54;
            for (int x = 0; x < width; x++) {
                const int x_2 = x / 2;
                const uchar Y = data[Y_offset + x];
                const uchar U = data[U_offset + x_2];
                const uchar V = data[V_offset + x_2];
                *pixel = yuvToGray(Y, U, V);
                ++pixel;
            }
        }
    }

    // nv12 format, encountered on macOS
    if(image.isNull() && videoFrame.pixelFormat == QVideoFrame::Format_NV12) {
        image = QImage(videoFrame.size, QImage::Format_Grayscale8);
        uchar* pixel = image.bits();
        const uchar* y_data = data;
        const uchar* uv_data = data + (height * width);
        for (int y = 0; y < height; y++) {
            const int w_y_2 = width * int(y / 2); // floored half-y
            for (int x = 0; x < width; x++) {
                const uchar Y = *y_data;
                const int uv_index = (w_y_2 + x / 2) * 2;
                const uchar U = uv_data[uv_index];
                const uchar V = uv_data[uv_index + 1];
                y_data++;
                *pixel = yuvToGray(Y, U, V);
                ++pixel;
            }
        }
    }

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

    if (!captureRect.isEmpty())
        image = image.copy(captureRect);

//    qDebug() << "image.size()" << image.size();
//    qDebug() << "image.format()" << image.format();
//    qDebug() << "videoFrame.pixelFormat" << videoFrame.pixelFormat;

//    const QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/qrtest/test_" + QString::number(i % 100) + ".png";
//    qDebug() << "saving image" << i << "at:" << path << image.save(path);

    QString tag = filter->decoder.decodeImage(image, image.width(), image.height());

    const bool tryHarder = filter->decoder.getTryHarder();
    /// The frames we get from the camera may be reflected horizontally or vertically
    /// As the decoder can't handle reflected frames, we swap them in all possible frames, changing the swap mode each frame.
    /// TODO: Maybe there is a better way to know this orientation beforehand? Or should we try decoding all of them?
    if (tag.isEmpty() && tryHarder) {
        image = image.mirrored(true, false);
        tag = filter->decoder.decodeImage(image, image.width(), image.height());
    }
    if (tag.isEmpty() && tryHarder) {
        image = image.mirrored(false, true);
        tag = filter->decoder.decodeImage(image, image.width(), image.height());
    }
    if (tag.isEmpty() && tryHarder) {
        image = image.mirrored(true, true);
        tag = filter->decoder.decodeImage(image, image.width(), image.height());
    }
}
