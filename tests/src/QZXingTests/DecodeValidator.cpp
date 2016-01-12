#include "DecodeValidator.h"

#include <QFile>
#include <QDirIterator>
#include <QFileInfo>

DecodeValidator::DecodeValidator() : decoder()
{
}

QString DecodeValidator::getDataFromTextFile(const QString &filePath)
{
    QFile f(filePath);
    if (!f.open(QFile::ReadOnly | QFile::Text))
        return "";
    QTextStream in(&f);
    return in.readAll();
}

std::shared_ptr<ValidationStats> DecodeValidator::testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder, const QImage &imageToDecode, const QString &expectedOutput)
{
    std::shared_ptr<ValidationStats> stats_ = std::make_shared<ValidationStats>();

    decoder.setDecoder(enabledDecoder);

    QString result = decoder.decodeImage(imageToDecode, 999, 999, true);

    stats_->setElaspedTime(decoder.getProcessTimeOfLastDecoding());
    stats_->setOperationSuccess(result != "");
    stats_->setResultMatch(result == expectedOutput);

    return stats_;
}

std::shared_ptr<ValidationStats> DecodeValidator::testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder, const QString &imageToDecodePath, const QString &expectedOutputFilePath)
{
   // QUrl imageUrl(imageToDecodePath);
    QImage tmpImage = QImage(imageToDecodePath);//imageUrl.toLocalFile());
    QString expectedOutput = getDataFromTextFile(expectedOutputFilePath);

    std::shared_ptr<ValidationStats> stats_ = testDecodeWithExpectedOutput(enabledDecoder, tmpImage, expectedOutput);

    stats_->setImagePath(imageToDecodePath);
    stats_->setExpectedOutput(expectedOutput);

    qDebug() << "Operation success: " << stats_->getOperationSuccess()
             << ", Result Match: " << stats_->getResultMatch()
             << ", Path: " << stats_->getImagePath()
             //<< ", Expected Output: " << stats_->getExpectedOutput()
                ;
    return stats_;
}

void DecodeValidator::decodeAllImagesInForderWithValidator(QZXing::DecoderFormat enabledDecoder, const QString &folderPath)
{
    QDirIterator dirIt(folderPath, QDirIterator::NoIteratorFlags);

    testResults[enabledDecoder] = std::vector<std::shared_ptr<ValidationStats>>();

    while (dirIt.hasNext()) {
        dirIt.next();
        QFileInfo fileInfo(dirIt.filePath());
        if (fileInfo.isFile() && fileInfo.suffix() != "txt") {
            QString imagePath = dirIt.filePath();
            QString expectedOutputTextFile = fileInfo.absoluteDir().absolutePath() + "/" + fileInfo.baseName() + ".txt";

            testResults[enabledDecoder].push_back(testDecodeWithExpectedOutput(enabledDecoder, imagePath, expectedOutputTextFile));
        }
    }
}

void DecodeValidator::executeTests()
{
    decodeAllImagesInForderWithValidator(QZXing::DecoderFormat_Aztec, "../../resources/aztec-1");
    decodeAllImagesInForderWithValidator(QZXing::DecoderFormat_Aztec, "../../resources/aztec-2");
    decodeAllImagesInForderWithValidator(QZXing::DecoderFormat_QR_CODE, "../../resources/qrcode-1");
    decodeAllImagesInForderWithValidator(QZXing::DecoderFormat_QR_CODE, "../../resources/qrcode-2");
    decodeAllImagesInForderWithValidator(QZXing::DecoderFormat_QR_CODE, "../../resources/qrcode-3");
    decodeAllImagesInForderWithValidator(QZXing::DecoderFormat_QR_CODE, "../../resources/qrcode-4");
}


