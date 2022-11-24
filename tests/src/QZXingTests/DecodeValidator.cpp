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
    connect(&decoder, SIGNAL(tagFoundAdvanced(const QString&, const QString&, const QString&)),
            this, SLOT(tagFound(const QString&, const QString&, const QString&)));

    connect(&decoder, SIGNAL(decodingFinished(bool)),
            this, SLOT(decodingFinished(bool)));

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
    std::shared_ptr<ValidationStats> stats = std::make_shared<ValidationStats>();

//    decoder.setDecoder(enabledDecoder);

    QString result = decoder.decodeImage(imageToDecode);
    result.replace("\r\n","\n");

    stats->setElaspedTime(decoder.getProcessTimeOfLastDecoding());
    stats->setOperationSuccess(result != "");
    stats->setResultMatch(expectedOutput != "" && result == expectedOutput);

    if(!stats->getResultMatch() && stats->getOperationSuccess()) {
        qDebug() << "Expected: " << expectedOutput;
        qDebug() << "Decoded:  " << result;
    }

    return stats;
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
    size_t finalSuccessful = 0;
    size_t finalFailed = 0;
    size_t finalInconsistent = 0;

     std::map<QString, std::shared_ptr<ValidationStats>>::iterator it;
      for(it=results.begin(); it != results.end(); it++) {
          std::shared_ptr<ValidationStats> &results = it->second;

          QFileInfo file(it->first);
          qDebug().noquote()<< file.dir().dirName() << "/"  << file.fileName() << " | "
                   << (results->getOperationSuccess() ? "Decode Success" : "Decode Failed") << " | "
                   << results->getDecodedFormat();

          if(results->getOperationSuccess())
              finalSuccessful++;
          else
              finalFailed++;

          if(!results->getResultMatch())
              finalInconsistent++;
      }
      qDebug() << "Total: [" << (results.size()) << "]"
               << ", successful: [" << finalSuccessful << "]"
               << ", failed: [" << finalFailed << "]"
               << ", inconsistencies: [" << finalInconsistent << "]";
}

std::shared_ptr<ValidationStats> DecodeValidator::testDecodeWithExpectedOutput(QZXing::DecoderFormat enabledDecoder, const QString &imageToDecodePath, const QString &expectedOutputFilePath)
{
    QImage tmpImage = QImage(imageToDecodePath);
    QString expectedOutput = getDataFromTextFile(expectedOutputFilePath);
    QString fmtFile = expectedOutputFilePath.left(expectedOutputFilePath.lastIndexOf('.')).append(".fmt");
    QString expectedFormat = getDataFromTextFile(fmtFile).trimmed();
    current_stats = std::make_shared<ValidationStats>();
    current_stats->setImagePath(imageToDecodePath);
    current_stats->setExpectedOutput(expectedOutput);
    current_stats->setExpectedFormat(expectedFormat);

    QString result = decoder.decodeImage(tmpImage);
    result.replace("\r\n","\n");

    current_stats->setElaspedTime(decoder.getProcessTimeOfLastDecoding());

    return current_stats;
}

void DecodeValidator::decodeAllImagesInForderWithValidator(QZXing::DecoderFormat enabledDecoder, const QString &folderPath)
{
    QDirIterator dirIt(folderPath, QDirIterator::NoIteratorFlags);

    while (dirIt.hasNext()) {
        dirIt.next();
        QFileInfo fileInfo(dirIt.filePath());
        if (fileInfo.isFile() && fileInfo.suffix() != "txt" && fileInfo.suffix() != "fmt") {
            QString imagePath = dirIt.filePath();
            qDebug()<<"Decoding : "<<imagePath;
            QString expectedOutputTextFile = fileInfo.absoluteDir().absolutePath() + "/" + fileInfo.baseName() + ".txt";

            testDecodeWithExpectedOutput(enabledDecoder, imagePath, expectedOutputTextFile);
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

void DecodeValidator::tagFound(const QString &tag, const QString &format, const QString &charSet)
{
    current_stats->setDecodedFormat(format);
    current_stats->setResultMatch(tag == current_stats->getExpectedOutput() &&
                                  format == current_stats->getExpectedFormat() );

}

void DecodeValidator::decodingFinished(bool result)
{
    current_stats->setOperationSuccess(result);
    results[current_stats->getImagePath()] = current_stats;
}



