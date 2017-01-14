#include "CameraImageWrapper.h"
#include <QColor>

CameraImageWrapper::CameraImageWrapper() : LuminanceSource(0,0), image(NULL)
{
}

CameraImageWrapper::CameraImageWrapper(const QImage &sourceImage) : LuminanceSource(sourceImage.width(), sourceImage.height())
{
    if (sourceImage.format() != QImage::Format_Grayscale8) {
        image = sourceImage.convertToFormat(QImage::Format_Grayscale8);
    } else {
        image = sourceImage;
    }

    delegate = Ref<GreyscaleLuminanceSource>(
                new GreyscaleLuminanceSource(getMatrixP(), image.width(), image.height(),0, 0, image.width(), image.height()));
}

CameraImageWrapper::CameraImageWrapper(CameraImageWrapper& otherInstance) : LuminanceSource(otherInstance.getWidth(), otherInstance.getHeight())
{
    image = otherInstance.getOriginalImage();
    delegate = otherInstance.getDelegate();
}

CameraImageWrapper::~CameraImageWrapper()
{
}

CameraImageWrapper *CameraImageWrapper::Factory(const QImage &sourceImage, int maxWidth, int maxHeight, bool smoothTransformation)
{
    if((maxWidth != 1 && sourceImage.width() > maxWidth) || (maxHeight != 1 && sourceImage.height() > maxHeight))
    {
        QImage image;
        image = sourceImage.scaled(
                    maxWidth != -1 ? maxWidth : sourceImage.width(),
                    maxHeight != -1 ? maxHeight : sourceImage.height(),
                    Qt::KeepAspectRatio,
                    smoothTransformation ? Qt::SmoothTransformation : Qt::FastTransformation);
        return new CameraImageWrapper(image);
    }
    else
        return new CameraImageWrapper(sourceImage);
}

QImage CameraImageWrapper::getOriginalImage()
{
    return image;
}

ArrayRef<byte> CameraImageWrapper::getRow(int y, ArrayRef<byte> row) const
{
    if(delegate)
        return delegate->getRow(y, row);
    else
        return getRowP(y, row);
}

ArrayRef<byte> CameraImageWrapper::getMatrix() const
{
    if(delegate)
        return delegate->getMatrix();
    else
        return getMatrixP();
}

bool CameraImageWrapper::isCropSupported() const
{
    if(delegate)
        return delegate->isCropSupported();
    else
        return LuminanceSource::isCropSupported();
}

Ref<LuminanceSource> CameraImageWrapper::crop(int left, int top, int width, int height) const
{
    if(delegate)
        return delegate->crop(left, top, width, height);
    else
        return LuminanceSource::crop(left, top, width, height);
}

bool CameraImageWrapper::isRotateSupported() const
{
    if(delegate)
        return delegate->isRotateSupported();
    else
        return LuminanceSource::isRotateSupported();
}

Ref<LuminanceSource> CameraImageWrapper::invert() const
{
    if(delegate)
        return delegate->invert();
    else
        return LuminanceSource::invert();
}

Ref<LuminanceSource> CameraImageWrapper::rotateCounterClockwise() const
{
    if(delegate)
        return delegate->rotateCounterClockwise();
    else
        return LuminanceSource::rotateCounterClockwise();
}

ArrayRef<byte> CameraImageWrapper::getRowP(int y, ArrayRef<byte> row) const
{
    int width = getWidth();

    if (row->size() != width)
        row.reset(ArrayRef<byte>(width));

    Q_ASSERT(image.format() == QImage::Format_Grayscale8);
    memcpy(row->values().data(), image.constScanLine(y), width);
    return row;
}

ArrayRef<byte> CameraImageWrapper::getMatrixP() const
{
    const int width = getWidth();
    const int height = getHeight();

    ArrayRef<byte> arr(width*height);

    memcpy(arr->values().data(), image.constBits(), width * height);

    return arr;
}
