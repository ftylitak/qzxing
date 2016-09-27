#ifndef QZXingFilter_H
#define QZXingFilter_H

#include <QObject>
#include <QAbstractVideoFilter>
#include <QZXing.h>

///
/// References:
///
/// https://blog.qt.io/blog/2015/03/20/introducing-video-filters-in-qt-multimedia/
/// http://doc.qt.io/qt-5/qabstractvideofilter.html
/// http://doc.qt.io/qt-5/qml-qtmultimedia-videooutput.html#filters-prop
/// http://doc.qt.io/qt-5/qvideofilterrunnable.html
/// http://doc.qt.io/qt-5/qtconcurrent-runfunction-main-cpp.html
///

/// This is used to store a QVideoFrame info while we are searching the image for QRCodes.
struct SimpleVideoFrame
{
    QByteArray data;
    QSize size;
    QVideoFrame::PixelFormat pixelFormat;

    SimpleVideoFrame()
        : size{0,0}
        , pixelFormat{QVideoFrame::Format_Invalid}
    {}

    SimpleVideoFrame(QVideoFrame & frame)
    {
        copyData(frame);
    }

    void copyData(QVideoFrame & frame)
    {
        frame.map(QAbstractVideoBuffer::ReadOnly);

        /// Copy video frame bytes to this.data
        /// This is made to try to get a better performance (less memory allocation, faster unmap)
        /// Any other task is performed in a QFuture task, as we want to leave the UI thread asap
        if(data.size() != frame.mappedBytes())
        {
            qDebug() << "needed to resize";
            data.resize(frame.mappedBytes());
        }
        memcpy(data.data(), frame.bits(), frame.mappedBytes());
        size = frame.size();
        pixelFormat = frame.pixelFormat();

        frame.unmap();
    }
};

/// Video filter is the filter that has to be registered in C++, instantiated and attached in QML
class QZXingFilter : public QAbstractVideoFilter
{
    friend class QZXingFilterRunnable;

    Q_OBJECT
        Q_PROPERTY(bool decoding READ isDecoding NOTIFY isDecodingChanged)

    signals:
        void isDecodingChanged();
        void decodingFinished(bool succeeded, int decodeTime);
        void tagFound(QString tag);
        void decodingStarted();

    private slots:
        void handleDecodingStarted();
        void handleDecodingFinished(bool succeeded);
        void handleTagFound(QString tag);

    private: /// Attributes
        QZXing decoder;
        bool decoding;

        SimpleVideoFrame frame;
        QFuture<void> processThread;

    public:  /// Methods
        explicit QZXingFilter(QObject *parent = 0);
        virtual ~QZXingFilter();

        bool isDecoding() {return decoding; }

        QVideoFilterRunnable * createFilterRunnable();

        static QImage fromBGRAtoARGB(uchar * data, QSize size, QVideoFrame::PixelFormat pixelFormat);
};

/// A new Runnable is created everytime the filter gets a new frame
class QZXingFilterRunnable : public QObject, public QVideoFilterRunnable
{
    Q_OBJECT

    public:
        explicit QZXingFilterRunnable(QZXingFilter * filter);
        /// This method is called whenever we get a new frame. It runs in the UI thread.
        QVideoFrame run(QVideoFrame * input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);
        void processVideoFrameProbed(SimpleVideoFrame & videoFrame);

    private:
        QZXingFilter * filter;
};

#endif // QZXingFilter_H
