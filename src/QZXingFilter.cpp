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
    /// Connecting signals to handlers that will send signals to QML
    connect(&decoder, &QZXing::decodingStarted,
            this, &QZXingFilter::handleDecodingStarted);
    connect(&decoder, &QZXing::decodingFinished,
            this, &QZXingFilter::handleDecodingFinished);
}

QZXingFilter::~QZXingFilter()
{
    if(!processThread.isFinished()) {
      processThread.cancel();
      processThread.waitForFinished();
    }
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

///
/// QZXingFilterRunnable
///

QZXingFilterRunnable::QZXingFilterRunnable(QZXingFilter * filter)
    : QObject(nullptr)
    , filter(filter)
{

}
QZXingFilterRunnable::~QZXingFilterRunnable()
{
    filter = nullptr;
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

static bool isRectValid(const QRect& rect)
{
  return rect.x() >= 0 && rect.y() >= 0 && rect.isValid();
}

static QImage rgbDataToGrayscale(const uchar* data, const int width, const int height,
                                 const int alpha, const int red,
                                 const int green, const int blue,
                                 const QRect& captureRect,
                                 const bool isPremultiplied = false)
{
    const int stride = (alpha < 0) ? 3 : 4;

    const int startX = isRectValid(captureRect) ? captureRect.x() : 0;
    const int startY = isRectValid(captureRect) ? captureRect.y() : 0;
    const int targetWidth = isRectValid(captureRect) ? captureRect.width() : width;
    const int targetHeight = isRectValid(captureRect) ? captureRect.height() : height;
    const int endX = width - startX - targetWidth;
    const int skipX = (endX + startX ) * stride;

    QImage image(targetWidth, targetHeight, QImage::Format_Grayscale8);
    uchar* pixelInit = image.bits();
    data += (startY * width + startX) * stride;
    for (int y = 1; y <= targetHeight; ++y) {
        uchar* pixel = pixelInit + (targetHeight - y) * targetWidth;
        for (int x = 0; x < targetWidth; ++x) {
            uchar r = data[red];
            uchar g = data[green];
            uchar b = data[blue];
            if (isPremultiplied) {
                uchar a = data[alpha];
                r = (uint(r) * 255) / a;
                g = (uint(g) * 255) / a;
                b = (uint(b) * 255) / a;
            }
            *pixel = gray(r, g, b);
            ++pixel;
            data += stride;
        }
        data += skipX;
    }

//    QTransform myTransform;
//    myTransform.rotate(180);
//    myTransform.scale(-1, 1);
//    return image.transformed(myTransform);

    //    static int cnt = 0;
    //    QImage image_pre(width, height, QImage::Format_RGB32);
    //    memcpy(image_pre.bits(), data, width*height*stride);
    //    image_pre.save("D:\\tmp\\" + QString::number(cnt++) + ".png");

    return image;
}

void QZXingFilterRunnable::processVideoFrameProbed(SimpleVideoFrame & videoFrame, const QRect& captureRect)
{
    static unsigned int i = 0; i++;
//    qDebug() << "Future: Going to process frame: " << i;

    const int width = videoFrame.size.width();
    const int height = videoFrame.size.height();
    const uchar* data = (uchar*) videoFrame.data.constData();
    /// Create QImage from QVideoFrame.
    QImage image;

    /// Let's try to convert it from RGB formats
    if (videoFrame.pixelFormat == QVideoFrame::Format_RGB32)
        image = rgbDataToGrayscale(data, width, height, 0, 1, 2, 3, captureRect);
    else if (videoFrame.pixelFormat == QVideoFrame::Format_ARGB32)
        image = rgbDataToGrayscale(data, width, height, 0, 1, 2, 3, captureRect);
    else if (videoFrame.pixelFormat == QVideoFrame::Format_ARGB32_Premultiplied)
        image = rgbDataToGrayscale(data, width, height, 0, 1, 2, 3, captureRect, true);
    else if (videoFrame.pixelFormat == QVideoFrame::Format_BGRA32)
        image = rgbDataToGrayscale(data, width, height, 3, 2, 1, 0, captureRect);
    else if (videoFrame.pixelFormat == QVideoFrame::Format_BGRA32_Premultiplied)
        image = rgbDataToGrayscale(data, width, height, 3, 2, 1, 0, captureRect, true);
    else if (videoFrame.pixelFormat == QVideoFrame::Format_BGR32)
        image = rgbDataToGrayscale(data, width, height, 3, 2, 1, 0, captureRect);
    else if (videoFrame.pixelFormat == QVideoFrame::Format_BGR24)
        image = rgbDataToGrayscale(data, width, height, -1, 2, 1, 0, captureRect);

    /// This is a forced "conversion", colors end up swapped.
    if(image.isNull() && videoFrame.pixelFormat == QVideoFrame::Format_BGR555)
        image = QImage(data, width, height, QImage::Format_RGB555);

    /// This is a forced "conversion", colors end up swapped.
    if(image.isNull() && videoFrame.pixelFormat == QVideoFrame::Format_BGR565)
        image = QImage(data, width, height, QImage::Format_RGB16);

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

    if (image.isNull()) {
        QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat);
        image = QImage(data, width, height, imageFormat);
    }

    if(image.isNull())
    {
        qDebug() << "QZXingFilterRunnable error: Cant create image file to process.";
        qDebug() << "Maybe it was a format conversion problem? ";
        qDebug() << "VideoFrame format: " << videoFrame.pixelFormat;
        qDebug() << "Image corresponding format: " << QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat);
        filter->decoding = false;
        return;
    }

    if (isRectValid(captureRect) && image.size() != captureRect.size())
        image = image.copy(captureRect);

//    qDebug() << "image.size()" << image.size();
//    qDebug() << "image.format()" << image.format();
//    qDebug() << "videoFrame.pixelFormat" << videoFrame.pixelFormat;

//    const QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/qrtest/test_" + QString::number(i % 100) + ".png";
//    qDebug() << "saving image" << i << "at:" << path << image.save(path);

    QString tag = decode(image);

    const bool tryHarder = filter->decoder.getTryHarder();
    /// The frames we get from the camera may be reflected horizontally or vertically
    /// As the decoder can't handle reflected frames, we swap them in all possible frames, changing the swap mode each frame.
    /// TODO: Maybe there is a better way to know this orientation beforehand? Or should we try decoding all of them?
    if (tag.isEmpty() && tryHarder) {
        image = image.mirrored(true, false);
        tag = decode(image);
    }
    if (tag.isEmpty() && tryHarder) {
        image = image.mirrored(false, true);
        tag = decode(image);
    }
    if (tag.isEmpty() && tryHarder) {
        image = image.mirrored(true, true);
        tag = decode(image);
    }
}

QString QZXingFilterRunnable::decode(const QImage &image)
{
    return (filter != nullptr) ?
      filter->decoder.decodeImage(image, image.width(), image.height()) : QString();
}
