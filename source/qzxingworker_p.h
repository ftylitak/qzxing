#ifndef QZXINGWORKER_P_H
#define QZXINGWORKER_P_H

#include <QObject>
#include <QImage>

class QZXingWorker_p : public QObject
{
    Q_OBJECT
public:
    explicit QZXingWorker_p(QObject *parent = 0);
    
signals:
    void decodingStarted();
    void decodingFinished(bool succeeded);
    void tagFound(QString tag);
    
public slots:
    void setData(int* processingTime, QImage image, int maxWidth, int maxHeight, bool smoothTransformation,
                 void* decoder, uint enabledDecoders);
    QString decode();

private:
    int* processingTime;
    QImage image;
    int maxWidth;
    int maxHeight;
    bool smoothTransformation;
    void* decoder;
    uint enabledDecoders;
};

#endif // QZXINGWORKER_P_H
