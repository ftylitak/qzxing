#ifndef DECODEVALIDATOR_H
#define DECODEVALIDATOR_H

#include "ValidationStats.h"
#include "QZXing.h"
#include <memory>
#include <vector>
#include <map>
#include <QMap>

class DecodeValidator
{
private:
    QZXing decoder;
    std::map<QString,QZXing::DecoderFormat> decoderCorrelationMap;
    std::map<QZXing::DecoderFormat, std::vector<std::shared_ptr<ValidationStats>>> testResults;

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
};

#endif // DECODEVALIDATOR_H
