#ifndef DECODEVALIDATOR_H
#define DECODEVALIDATOR_H

#include "ValidationStats.h"
#include <QZXing.h>
#include <memory>
#include <vector>
#include <map>

class DecodeValidator
{
private:
    QZXing decoder;
    std::map<QZXing::DecoderFormat, std::vector<std::shared_ptr<ValidationStats>>> testResults;

    QString getDataFromTextFile(const QString &filePath);

    std::shared_ptr<ValidationStats> testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder,
                                                 const QImage &imageToDecode,
                                                 const QString &expectedOutput);

public:
    DecodeValidator();

    std::shared_ptr<ValidationStats> testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder,
                                                 const QString &imageToDecodePath,
                                                 const QString &expectedOutputFilePath);

    void decodeAllImagesInForderWithValidator(QZXing::DecoderFormat enabledDecode,
                                              const QString &folderPath);

    void executeTests();
};

#endif // DECODEVALIDATOR_H
