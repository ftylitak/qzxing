#ifndef CAMERAIMAGE_H
#define CAMERAIMAGE_H

#include <QImage>
#include <QString>
#include <zxing/zxing/LuminanceSource.h>

using namespace zxing;

class CameraImageWrapper : public LuminanceSource
{
public:
    CameraImageWrapper();
    CameraImageWrapper(QImage& image);
    CameraImageWrapper(CameraImageWrapper& otherInstance);
    ~CameraImageWrapper();
    
    int getWidth() const;
    int getHeight() const;
    
    unsigned char getPixel(int x, int y) const;
    unsigned char* copyMatrix() const;
    
    /**
      * Set the source of the image. If it fails,  returns false.
      */
    bool setImage(QString fileName, int maxWidth=-1, int maxHeight=-1);
    bool setImage(QImage newImage, int maxWidth=-1, int maxHeight=-1);

    QImage grayScaleImage(QImage::Format f);
    QImage getOriginalImage();


    // Callers take ownership of the returned memory and must call delete [] on it themselves.
    //unsigned char* getRow(int y, unsigned char* row);
    //unsigned char* getMatrix();

    ArrayRef<char> getRow(int y, ArrayRef<char> row) const;
    ArrayRef<char> getMatrix() const;

    void setSmoothTransformation(bool enable);

private:
    void scale(int maxWidth, int maxHeight);
  
private:
    QImage image;
    unsigned char* pRow;
    unsigned char* pMatrix;
    bool isSmoothTransformationEnabled;
};

#endif //CAMERAIMAGE_H
