#ifndef CAMERAIMAGE_H
#define CAMERAIMAGE_H

#include <QImage>
#include <QString>
#include <zxing/zxing/common/GreyscaleLuminanceSource.h>

using namespace zxing;

class CameraImageWrapper : public LuminanceSource
{
public:
    CameraImageWrapper();
    CameraImageWrapper(const QImage& sourceImage);
    CameraImageWrapper(CameraImageWrapper& otherInstance);
    ~CameraImageWrapper();

    static CameraImageWrapper* Factory(const QImage& image, int maxWidth=-1, int maxHeight=-1, bool smoothTransformation=false);
    
    QImage getOriginalImage();
    Ref<GreyscaleLuminanceSource> getDelegate() { return delegate; }

    ArrayRef<zxing::byte> getRow(int y, ArrayRef<zxing::byte> row) const;
    ArrayRef<zxing::byte> getMatrix() const;

    bool isCropSupported() const;
    Ref<LuminanceSource> crop(int left, int top, int width, int height) const;
    bool isRotateSupported() const;
    Ref<LuminanceSource> invert() const;
    Ref<LuminanceSource> rotateCounterClockwise() const;
  
private:
    ArrayRef<zxing::byte> getRowP(int y, ArrayRef<zxing::byte> row) const;
    ArrayRef<zxing::byte> getMatrixP() const;

    QImage image;
    Ref<GreyscaleLuminanceSource> delegate;
};

#endif //CAMERAIMAGE_H
