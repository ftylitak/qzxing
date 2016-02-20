#include "CameraImageWrapper.h"
#include <QColor>
#include <QApplication>
#include <QDesktopWidget>

CameraImageWrapper::CameraImageWrapper() : LuminanceSource(0,0), image(NULL)
{
}

CameraImageWrapper::CameraImageWrapper(const QImage &sourceImage) : LuminanceSource(sourceImage.width(), sourceImage.height())
{
    image = grayScaleImage( &sourceImage );
}

CameraImageWrapper::CameraImageWrapper(CameraImageWrapper& otherInstance) : LuminanceSource(otherInstance.getWidth(), otherInstance.getHeight())
{
    image = new QImage(otherInstance.getOriginalImage());
}

CameraImageWrapper::~CameraImageWrapper()
{
    if(image)
        delete image;
}

CameraImageWrapper *CameraImageWrapper::Factory(const QImage &sourceImage, int maxWidth, int maxHeight, bool smoothTransformation)
{
    if((maxWidth != 1 || maxHeight != 1) && (sourceImage.width() > maxWidth || sourceImage.height() > maxHeight))
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

int CameraImageWrapper::getWidth() const
{
    return image->width();
}

int CameraImageWrapper::getHeight() const
{
    return image->height();
}

unsigned char CameraImageWrapper::getPixel(int x, int y) const
{
    return image->pixel(x,y);
}

unsigned char* CameraImageWrapper::copyMatrix() const
{
    unsigned char* newMatrix = (unsigned char*)malloc(image->width() * image->height() * sizeof(unsigned char));

    int cnt = 0;
    for(int i=0; i<image->width(); i++)
        for(int j=0; j<image->height(); j++)
            newMatrix[cnt++] = getPixel(i,j);

    return newMatrix;
}

QImage* CameraImageWrapper::grayScaleImage(const QImage *origin)
{
    QImage *tmp = new QImage(origin->width(), origin->height(), QImage::Format_Grayscale8);
    for(int i=0; i<origin->width(); i++)
    {
        for(int j=0; j<origin->height(); j++)
        {
            int pix = qGray(origin->pixel(QPoint(i,j)));
            tmp->setPixel(i,j, qRgb(pix ,pix,pix));
        }
    }

    return tmp;
}

QImage CameraImageWrapper::getOriginalImage()
{
    return *image;
}

ArrayRef<char> CameraImageWrapper::getRow(int y, ArrayRef<char> row) const
{
    int width = getWidth();

    if (row->size() != width)
        row.reset(ArrayRef<char>(width));

    for (int x = 0; x < width; x++)
        row[x] = getPixel(x,y);

    return row;
}

ArrayRef<char> CameraImageWrapper::getMatrix() const
{
    int width = getWidth();
    int height =  getHeight();

    ArrayRef<char> tmpRow(0);
    ArrayRef<char> arr(width*height);

    char* m = &arr[0];

    for(int y=0; y<height; y++)
    {
        tmpRow = getRow(y, tmpRow);
#if __cplusplus > 199711L
        memcpy(m, tmpRow->values().data(), width);
#else
        memcpy(m, &tmpRow[0], width);
#endif
        m += width * sizeof(unsigned char);
    }

    return arr;
}

QImage *CameraImageWrapper::sharpen(const QImage *origin)
{
    QImage * newImage = new QImage(* origin);

    int kernel [3][3]= {{0,-1,0},
                        {-1,5,-1},
                        {0,-1,0}};
    int kernelSize = 3;
    int sumKernel = 1;
    int r,g,b;
    QColor color;

    for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
        for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++){

            r = 0;
            g = 0;
            b = 0;

            for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                    color = QColor(origin->pixel(x+i, y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                }
            }

            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));

        }
    }
    return newImage;
}
