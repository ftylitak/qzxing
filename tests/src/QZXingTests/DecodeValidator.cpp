#include "DecodeValidator.h"

#include <QFile>
#include <QDirIterator>
#include <QFileInfo>

DecodeValidator::DecodeValidator() : decoder(), decoderCorrelationMap(), testResults()
{
    initializeDecoderCorrelation();
}

void DecodeValidator::initializeDecoderCorrelation()
{
    decoderCorrelationMap["aztec"] = QZXing::DecoderFormat_Aztec;
    decoderCorrelationMap["codabar"] = QZXing::DecoderFormat_CODABAR;
    decoderCorrelationMap["code39"] = QZXing::DecoderFormat_CODE_39;
    decoderCorrelationMap["code93"] = QZXing::DecoderFormat_CODE_93;
    decoderCorrelationMap["code128"] = QZXing::DecoderFormat_CODE_128;
    decoderCorrelationMap["datamatrix"] = QZXing::DecoderFormat_DATA_MATRIX;
    decoderCorrelationMap["ean8"] = QZXing::DecoderFormat_EAN_8;
    decoderCorrelationMap["ean13"] = QZXing::DecoderFormat_EAN_13;
    decoderCorrelationMap["itf"] = QZXing::DecoderFormat_ITF;
    decoderCorrelationMap["pdf417"] = QZXing::DecoderFormat_PDF_417;
    decoderCorrelationMap["qrcode"] = QZXing::DecoderFormat_QR_CODE;
    decoderCorrelationMap["rss14"] = QZXing::DecoderFormat_RSS_14;
    decoderCorrelationMap["rssexpanded"] = QZXing::DecoderFormat_RSS_EXPANDED;
    decoderCorrelationMap["rssexpandedstacked"] = QZXing::DecoderFormat_RSS_EXPANDED; //???
    decoderCorrelationMap["upca"] = QZXing::DecoderFormat_UPC_A;
    decoderCorrelationMap["upce"] = QZXing::DecoderFormat_UPC_E;
    decoderCorrelationMap["upcean"] = QZXing::DecoderFormat_UPC_EAN_EXTENSION;
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

QZXing::DecoderFormat DecodeValidator::getDecoderForFolder(const QString &folderName)
{
    QStringList parts = folderName.split("-");

    if(!parts.size())
        return QZXing::DecoderFormat_None;

    std::map<QString,QZXing::DecoderFormat>::iterator it;
    it = decoderCorrelationMap.find(parts[0]);
    if (it != decoderCorrelationMap.end())
        return decoderCorrelationMap[parts[0]];
    else
        return QZXing::DecoderFormat_None;
}

std::shared_ptr<ValidationStats> DecodeValidator::testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder, const QString &imageToDecodePath, const QString &expectedOutputFilePath)
{
    QImage tmpImage = QImage(imageToDecodePath);
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
   // auto test =  std::vector<std::shared_ptr<ValidationStats>>();

    QDirIterator dirIt(folderPath, QDirIterator::NoIteratorFlags);

  // testResults.insert(enabledDecoder, std::move(test));

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

void DecodeValidator::executeTests(const QString &folderPath)
{
    QDirIterator dirIt(folderPath, QDirIterator::NoIteratorFlags);

    while (dirIt.hasNext()) {
        dirIt.next();
        QFileInfo fileInfo(dirIt.filePath());
        if (fileInfo.isDir()) {
            QString subfolderPath = dirIt.filePath();
            QString subfolderName = dirIt.fileName();

            QZXing::DecoderFormat decoderFormat = getDecoderForFolder(subfolderName);

            qDebug() << "Decoding folder: " << subfolderPath;
            if(decoderFormat != QZXing::DecoderFormat_None)
                decodeAllImagesInForderWithValidator(decoderFormat, subfolderPath);
        }
    }

}


