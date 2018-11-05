#include "DecodeValidator.h"

#include <QDebug>
#include <QFile>
#include <QDirIterator>
#include <QFileInfo>
#include <QTextStream>

#define LOG_OUTPUT_DIVIDER  "##############################################"
#define LOG_SECTOR_TITLE(a)    '\n' << LOG_OUTPUT_DIVIDER\
                               << '\n' << a\
                               << '\n' << LOG_OUTPUT_DIVIDER\
                               << '\n'

DecodeValidator::DecodeValidator() : decoder(), decoderCorrelationMap(), testResults()
{
    initializeDecoderCorrelation();
    decoder.setTryHarder(true);
}

void DecodeValidator::initializeDecoderCorrelation()
{
    decoderCorrelationMap["aztec"] = QZXing::DecoderFormat_Aztec;
    decoderCorrelationMap["codabar"] = QZXing::DecoderFormat_CODABAR;
    decoderCorrelationMap["code39"] = QZXing::DecoderFormat_CODE_39;
    decoderCorrelationMap["code93"] = QZXing::DecoderFormat_CODE_93;
    decoderCorrelationMap["code128"] = QZXing::DecoderFormat_CODE_128;
    decoderCorrelationMap["code128gs1"] = QZXing::DecoderFormat_CODE_128_GS1;
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

    QString result = decoder.decodeImage(imageToDecode);
    result.replace("\r\n","\n");

    stats_->setElaspedTime(decoder.getProcessTimeOfLastDecoding());
    stats_->setOperationSuccess(result != "");
    stats_->setResultMatch(expectedOutput != "" && result == expectedOutput);

    if(!stats_->getResultMatch() && stats_->getOperationSuccess()) {
        qDebug() << "Expected: " << expectedOutput;
        qDebug() << "Decoded:  " << result;
    }

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

void DecodeValidator::printResults()
{
    std::map<QZXing::DecoderFormat, std::vector<std::shared_ptr<ValidationStats>>>::iterator it;

    qDebug() << LOG_SECTOR_TITLE ("#  Test Results");

    size_t finalSuccessful = 0;
    size_t finalFailed = 0;
    size_t finalInconsistent = 0;

    for(it=testResults.begin(); it != testResults.end(); it++) {
        QString decoderStr = QZXing::decoderFormatToString(it->first);
        std::vector<std::shared_ptr<ValidationStats>> &resPerDecoder = it->second;

        size_t successfulTestCount = 0;
        QVector<QString> failedResultLogs;
        QVector<QString> inconsistentResultLogs;

        for(size_t i=0; i<resPerDecoder.size(); i++) {
            if(resPerDecoder[i]->getOperationSuccess())
                successfulTestCount++;
            else
                failedResultLogs.push_back(resPerDecoder[i]->getImagePath());

            if(resPerDecoder[i]->getOperationSuccess() && !resPerDecoder[i]->getResultMatch())
                inconsistentResultLogs.push_back(resPerDecoder[i]->getImagePath());
        }

        qDebug() << "Decoder: [" << decoderStr << "]"
                 << ", successful: [" << successfulTestCount << "]"
                 << ", failed: [" << failedResultLogs.size() << "]"
                 << ", inconsistencies: [" << inconsistentResultLogs.size() << "]";

        finalSuccessful += successfulTestCount;
        finalFailed += failedResultLogs.size();
        finalInconsistent += inconsistentResultLogs.size();

        if(failedResultLogs.size())
            qDebug() << "  failed image files:";

        for(int i=0; i<failedResultLogs.size(); i++)
            qDebug() << '\t' << failedResultLogs[i];

        if(inconsistentResultLogs.size())
            qDebug() << "  inconsistent image files:";

        for(int i=0; i<inconsistentResultLogs.size(); i++)
            qDebug() << '\t' << inconsistentResultLogs[i];
    }

    qDebug() << LOG_SECTOR_TITLE ("#  Total Results");
    qDebug() << "Total: [" << (finalSuccessful + finalFailed + finalInconsistent) << "]"
             << ", successful: [" << finalSuccessful << "]"
             << ", failed: [" << finalFailed << "]"
             << ", inconsistencies: [" << finalInconsistent << "]";
}

std::shared_ptr<ValidationStats> DecodeValidator::testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder, const QString &imageToDecodePath, const QString &expectedOutputFilePath)
{
    QImage tmpImage = QImage(imageToDecodePath);
    QString expectedOutput = getDataFromTextFile(expectedOutputFilePath);

    std::shared_ptr<ValidationStats> stats_ = testDecodeWithExpectedOutput(enabledDecoder, tmpImage, expectedOutput);

    stats_->setImagePath(imageToDecodePath);
    stats_->setExpectedOutput(expectedOutput);

    qDebug() << "Operation success: " << stats_->getOperationSuccess()
             << "\t, Result Match: " << stats_->getResultMatch()
             << "\t, Path: " << stats_->getImagePath();

    if(!stats_->getOperationSuccess() && stats_->getResultMatch())
        qDebug() << "\t[Warning]...";

    return stats_;
}

void DecodeValidator::decodeAllImagesInForderWithValidator(QZXing::DecoderFormat enabledDecoder, const QString &folderPath)
{
    QDirIterator dirIt(folderPath, QDirIterator::NoIteratorFlags);

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

    printResults();
}


