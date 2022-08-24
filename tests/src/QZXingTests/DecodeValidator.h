#ifndef DECODEVALIDATOR_H
#define DECODEVALIDATOR_H

#include "ValidationStats.h"
#include "QZXing.h"
#include <memory>
#include <vector>
#include <map>
#include <QMap>
#include <QObject>

class DecodeValidator: public QObject
{
    Q_OBJECT
private:
    QZXing decoder;
    std::map<QString,QZXing::DecoderFormat> decoderCorrelationMap;
    std::map<QZXing::DecoderFormat, std::vector<std::shared_ptr<ValidationStats>>> testResults;
    std::map<QString, std::shared_ptr<ValidationStats>> results;

    void initializeDecoderCorrelation();

    QString getDataFromTextFile(const QString &filePath);

    std::shared_ptr<ValidationStats> testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder,
                                                 const QImage &imageToDecode,
                                                 const QString &expectedOutput);

    QZXing::DecoderFormat getDecoderForFolder(const QString &folderName);

    void printResults();

public:
    DecodeValidator();

    std::shared_ptr<ValidationStats> testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder,
                                                 const QString &imageToDecodePath,
                                                 const QString &expectedOutputFilePath);

    void decodeAllImagesInForderWithValidator(QZXing::DecoderFormat enabledDecode,
                                              const QString &folderPath);

    void executeTests(const QString &folderPath);


    std::shared_ptr<ValidationStats> current_stats;
public slots:
  void tagFound(const QString& tag, const QString& format, const QString& charSet);
  void decodingFinished(bool);
};

#endif // DECODEVALIDATOR_H
