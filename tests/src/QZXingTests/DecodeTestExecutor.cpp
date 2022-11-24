#include "DecodeTestExecutor.h"
#include <QDebug>
#include <QDir>
#include <QFileInfoList>

int DecodeTestExecutor::fileCount = 0;

DecodeTestExecutor::DecodeTestExecutor(QString dirPath, QObject* parent) : QObject(parent){
    m_datasetPath = dirPath;

    initializeDecoderCorrelation();
    decoder.setTryHarder(true);

    connect(&decoder, SIGNAL(tagFoundAdvanced(const QString&, const QString&, const QString&)),
            this, SLOT(tagFound(const QString&, const QString&, const QString&)));

    connect(&decoder, SIGNAL(decodingFinished(bool)),
            this, SLOT(decodingFinished(bool)));
}

void DecodeTestExecutor::executeTest() {
    QFileInfo dirInfo(m_datasetPath);
    if (!dirInfo.isDir()) {
        qDebug() << m_datasetPath << "Doesn't seem to be valid directory";
        return;
    }

    QDir folder(m_datasetPath);

    QFileInfoList l = folder.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    qDebug() << "Fetching files to decode... ";
    for (int i = 0; i < l.count(); i++) {
        QFileInfo info = l.at(i);
        qDebug() << "Reading folder: " << info.absoluteFilePath();
        fetchFilesToDecode(info.absoluteFilePath());
    }
    qDebug() << "started decoding "<< fileCount<<" files.. ";
    startDecoding();
}

void DecodeTestExecutor::fetchFilesToDecode(QString path) {
    QDir curPath(path);
    curPath.setFilter(QDir::NoDotAndDotDot);
    QStringList images =
        curPath.entryList(QStringList() << "*.png", QDir::Files);

    foreach (QString file, images) {
        fileCount++;
        QString imgPath = curPath.path() + "/" + file;
        allFiles.enqueue(imgPath);
    }
}

void DecodeTestExecutor::startDecoding() {
    //dequeue a file and start decoding.
    if (!allFiles.isEmpty()) {
        QString file = allFiles.dequeue();
        QString exp = file.left(file.lastIndexOf('.')).append(".txt");
        QString expFormat = file.left(file.lastIndexOf('.')).append(".fmt");
        QFile expectedDataFile(exp);
        QFile expectedFormatFile(expFormat);
        m_expectedFormat = QZXing::DecoderFormat::DecoderFormat_None;
        if (expectedDataFile.open(QFile::ReadOnly)) {
            m_curentExpectedData = expectedDataFile.readAll();
        }
        if (expectedFormatFile.open(QFile::ReadOnly)) {
            m_expectedFormat =
                m_decoderCorrelationMap[expectedFormatFile.readAll()];
        }
        m_currentFile = file;
        decoder.decodeImageFromFile(file);
    } else {
        printResults();
    }
}

void DecodeTestExecutor::printResults() {
    qDebug() << "Decoded Results";

    qDebug() << "Total Files : " << DecodeTestExecutor::fileCount;
    qDebug() << "Decode Success count : " << m_successResults.count();
    qDebug() << "Decode Failure count : " << m_failedResults.count();
    qDebug() << "-----------------------------";
}


void DecodeTestExecutor::initializeDecoderCorrelation()
{
    m_decoderCorrelationMap["AZTEC"] = QZXing::DecoderFormat_Aztec;
    m_decoderCorrelationMap["CODABAR"] = QZXing::DecoderFormat_CODABAR;
    m_decoderCorrelationMap["CODE_39"] = QZXing::DecoderFormat_CODE_39;
    m_decoderCorrelationMap["CODE_93"] = QZXing::DecoderFormat_CODE_93;
    m_decoderCorrelationMap["CODE_128"] = QZXing::DecoderFormat_CODE_128;
    m_decoderCorrelationMap["DATA_MATRIX"] = QZXing::DecoderFormat_DATA_MATRIX;
    m_decoderCorrelationMap["EAN_8"] = QZXing::DecoderFormat_EAN_8;
    m_decoderCorrelationMap["EAN_13"] = QZXing::DecoderFormat_EAN_13;
    m_decoderCorrelationMap["ITF"] = QZXing::DecoderFormat_ITF;
    m_decoderCorrelationMap["PDF_417"] = QZXing::DecoderFormat_PDF_417;
    m_decoderCorrelationMap["QR_CODE"] = QZXing::DecoderFormat_QR_CODE;
    m_decoderCorrelationMap["RSS_14"] = QZXing::DecoderFormat_RSS_14;
    m_decoderCorrelationMap["RSS_EXPANDED"] = QZXing::DecoderFormat_RSS_EXPANDED;
    m_decoderCorrelationMap["UPC_A"] = QZXing::DecoderFormat_UPC_A;
    m_decoderCorrelationMap["UPC_E"] = QZXing::DecoderFormat_UPC_E;
    m_decoderCorrelationMap["UPC_EAN_EXTENSION"] = QZXing::DecoderFormat_UPC_EAN_EXTENSION;
    m_decoderCorrelationMap["CODE_128_GS1"] = QZXing::DecoderFormat_CODE_128_GS1;
}

void DecodeTestExecutor::tagFound(const QString& tag, const QString& format,
                            const QString& charSet) {
    Q_UNUSED(charSet);

    if (m_curentExpectedData == tag || m_expectedFormat == m_decoderCorrelationMap[format]) {
        qDebug() << m_currentFile << " Format : "<< format << "Decode Success";
        m_successResults.append(TestResult(m_currentFile, format, true));
    }
    else{
        m_failedResults.append(TestResult(m_currentFile,QString(""),false));
    }
}

void DecodeTestExecutor::decodingFinished(bool result) {
    if (!result) {
        qDebug() << m_currentFile << " Format : UNKNOWN" << "Decode Failure";
        m_failedResults.append(TestResult(m_currentFile,QString(""),false));
    }

    //After decoding a file has finished, fetch the next available file in the queue to decode.
    startDecoding();
}
